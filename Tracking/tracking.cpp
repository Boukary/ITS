#include "tracking.h"

using namespace std;
using namespace cv;

Tracking::Tracking(Buffer *buffer)
{
    buffer_ = buffer;
    is_running_ = false;
}

void Tracking::SetConfig(ConfigTracking config)
{
    config_ = config;
}

void Tracking::Start()
{
    is_running_ = true;
    this->start();
}

void Tracking::Stop()
{
    is_running_ = false;
}

bool Tracking::MainFunction()
{
    int index = buffer_->IsTrackingAvailable();
    unsigned long long index_absolu = buffer_->GetTrackingDataByIndex(index,image_,blobs_);
    vehicles_ = buffer_->GetVehicles();

    if (!TrackVehicles(index_absolu))
        return false;

    buffer_->UpdateVehicleListByTracking(&vehicles_);
    return buffer_->SetTrackingDataByIndex(index,index_absolu);
}

bool Tracking::TrackVehicles(unsigned long long index_absolu)
{
    regions_t m_regions;

    vector<Point_t> m_centers;

    for (int j = 0; j < blobs_.size(); ++j) {

        Rect bbox= blobs_[j].GetScope();
        CRegion region(bbox);
        Point2f center(bbox.x + 0.5f * bbox.width, bbox.y + 0.5f * bbox.height);

        m_regions.push_back(region);
        m_centers.push_back(Point_t(center.x, center.y));
    }

    assert(m_centers.size() == m_regions.size());

    if (config_.m_useLocalTracking)
    {
        local_tracker_.Update(tracks_, image_);
    }

    // -----------------------------------
    // If there is no tracks yet, then every cv::Point begins its own track.
    // -----------------------------------
    if (tracks_.size() == 0)
    {
        // If no tracks yet
        for (size_t i = 0; i < m_centers.size(); ++i)
        {
            tracks_.push_back(unique_ptr<CTrack>(new CTrack(m_centers[i], m_regions[i], config_.dt, config_.accelNoiseMag, config_.NextTrackID++, config_.m_kalmanType == FilterRect)));
        }
    }


    size_t N = tracks_.size();
    size_t M = m_centers.size();

    assignments_t assignment;

    if (!tracks_.empty())
    {
        distMatrix_t Cost(N * M);

        // -----------------------------------
        // -----------------------------------
        switch (config_.m_distType)
        {
        case CentersDist:
            for (size_t i = 0; i < tracks_.size(); i++)
            {
                for (size_t j = 0; j < m_centers.size(); j++)
                {
                    Cost[i + j * N] = tracks_[i]->CalcDist(m_centers[j]);
                }
            }
            break;

        case RectsDist:
            for (size_t i = 0; i < tracks_.size(); i++)
            {
                for (size_t j = 0; j < m_centers.size(); j++)
                {
                    Cost[i + j * N] = tracks_[i]->CalcDist(m_regions[j].m_rect);
                }
            }
            break;
        }
        // -----------------------------------
        // Solving assignment problem (tracks and predictions of Kalman filter)
        // -----------------------------------
        AssignmentProblemSolver APS;
        APS.Solve(Cost, N, M, assignment, AssignmentProblemSolver::optimal);

        // -----------------------------------
        // clean assignment from pairs with large distance
        // -----------------------------------
        for (size_t i = 0; i < assignment.size(); i++)
        {
            if (assignment[i] != -1)
            {
                if (Cost[i + assignment[i] * N] > config_.dist_thres)
                {
                    assignment[i] = -1;
                    tracks_[i]->skipped_frames++;
                }
            }
            else
            {
                // If track have no assigned detect, then increment skipped frames counter.
                tracks_[i]->skipped_frames++;
            }
        }

        // -----------------------------------
        // If track didn't get detects long time, remove it.
        // -----------------------------------
        for (int i = 0; i < static_cast<int>(tracks_.size()); i++)
        {
            if (tracks_[i]->skipped_frames > config_.maximum_allowed_skipped_frames)
            {
                tracks_.erase(tracks_.begin() + i);
                assignment.erase(assignment.begin() + i);
                i--;
            }
        }
    }

    // -----------------------------------
    // Search for unassigned detects and start new tracks for them.
    // -----------------------------------
    for (size_t i = 0; i < m_centers.size(); ++i)
    {
        if (find(assignment.begin(), assignment.end(), i) == assignment.end())
        {
            tracks_.push_back(unique_ptr<CTrack>(new CTrack(m_centers[i], m_regions[i], config_.dt, config_.accelNoiseMag, config_.NextTrackID++, config_.m_kalmanType == FilterRect)));
        }
    }



    // Update Kalman Filters state

    for (size_t i = 0; i<assignment.size(); i++)
    {
        // If track updated less than one time, than filter state is not correct.

        if (assignment[i] != -1) // If we have assigned detect, then update using its coordinates,
        {
            tracks_[i]->skipped_frames = 0;
            tracks_[i]->Update(m_centers[assignment[i]], m_regions[assignment[i]], true, config_.max_trace_length);
        }
        else				     // if not continue using predictions
        {
            tracks_[i]->Update(Point_t(), CRegion(), false, config_.max_trace_length);
        }
    }


    // Update Vehicle List

    VehicleBlob last_blob;

    // updating existing vehicles
    for (int i = 0; i < this->tracks_.size(); i++)
    {
        bool found =false;
        for (int j = 0; j < vehicles_.size(); ++j) {
            if (tracks_[i]->track_id == vehicles_.at(j).GetIdVehicle()){
                //if (tracks_[i]->GetLastRect().area() == 0)
                //   continue;
                last_blob.SetIndexAbsolu(index_absolu);
                last_blob.SetScope(tracks_[i]->GetLastRect());
                last_blob.SetCentroidImage2D(Point(tracks_[i]->GetLastRect().x+tracks_[i]->GetLastRect().width/2,tracks_[i]->GetLastRect().y+tracks_[i]->GetLastRect().height/2));

                vehicles_.at(j).AddBlob(last_blob);
                found = true;
                break;
            }
        }
    }

    // adding new vehicles
    for (int i = 0; i < this->tracks_.size(); i++)
    {
        bool found =false;
        for (int j = 0; j < vehicles_.size(); ++j) {
            if (tracks_[i]->track_id == vehicles_.at(j).GetIdVehicle()){
                found = true;
                break;
            }
        }
        if (!found){
            Vehicle new_vehicle;
            if (tracks_[i]->GetLastRect().area() == 0)
                continue;
            last_blob.SetIndexAbsolu(index_absolu);
            last_blob.SetScope(tracks_[i]->GetLastRect());
            last_blob.SetCentroidImage2D(Point(tracks_[i]->GetLastRect().x+tracks_[i]->GetLastRect().width/2,tracks_[i]->GetLastRect().y+tracks_[i]->GetLastRect().height/2));

            new_vehicle.AddBlob(last_blob);
            vehicles_.push_back(new_vehicle);
        }
    }


    // removing vehicles
    for (int i = 0; i < vehicles_.size(); i++)
    {
        bool found =false;

        for (int j = 0; j < this->tracks_.size(); ++j) {
            if (tracks_[j]->track_id == vehicles_.at(i).GetIdVehicle()){
                found = true;
                break;
            }
        }

        if (!found){
            vehicles_.erase(vehicles_.begin()+i,vehicles_.begin()+i+1);
            i--;
        }
    }


    return true;
}

void Tracking::run()
{
    double timer;
    while(is_running_){
        timer = (double)getTickCount();

        MainFunction();

        fps_ = getTickFrequency() / ((double)getTickCount() - timer);
    }
}

// in case of bad performance see :
// https://github.com/Smorodov/Multitarget-tracker (updated version of current implementation)
// https://github.com/samuelmurray/tracking-by-detection
// code hamd
