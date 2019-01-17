#-------------------------------------------------
#
# Project created by QtCreator 2018-12-24T19:46:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ITS
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    Buffer/buffer.cpp \
    Buffer/frame.cpp \
    Buffer/vehicle.cpp \
    Buffer/configscene.cpp \
    Buffer/imageindexed.cpp \
    Buffer/vehicleblob.cpp \
    Buffer/infraction.cpp \
    Buffer/region.cpp \
    Buffer/trafficsignalregion.cpp \
    Acquisition/acquisition.cpp \
    Preprocessing/preprocessing.cpp \
    Detection/detection.cpp \
    Detection/bgslibrary/package_analysis/ForegroundMaskAnalysis.cpp \
    Detection/bgslibrary/package_analysis/PerformanceUtils.cpp \
    Detection/bgslibrary/package_analysis/PixelUtils.cpp \
    Detection/bgslibrary/package_bgs/_template_/amber/amber.cpp \
    Detection/bgslibrary/package_bgs/_template_/Amber.cpp \
    Detection/bgslibrary/package_bgs/_template_/MyBGS.cpp \
    Detection/bgslibrary/package_bgs/dp/AdaptiveMedianBGS.cpp \
    Detection/bgslibrary/package_bgs/dp/Eigenbackground.cpp \
    Detection/bgslibrary/package_bgs/dp/Error.cpp \
    Detection/bgslibrary/package_bgs/dp/GrimsonGMM.cpp \
    Detection/bgslibrary/package_bgs/dp/Image.cpp \
    Detection/bgslibrary/package_bgs/dp/MeanBGS.cpp \
    Detection/bgslibrary/package_bgs/dp/PratiMediodBGS.cpp \
    Detection/bgslibrary/package_bgs/dp/TextureBGS.cpp \
    Detection/bgslibrary/package_bgs/dp/WrenGA.cpp \
    Detection/bgslibrary/package_bgs/dp/ZivkovicAGMM.cpp \
    Detection/bgslibrary/package_bgs/IMBS/IMBS.cpp \
    Detection/bgslibrary/package_bgs/KDE/KernelTable.cpp \
    Detection/bgslibrary/package_bgs/KDE/NPBGmodel.cpp \
    Detection/bgslibrary/package_bgs/KDE/NPBGSubtractor.cpp \
    Detection/bgslibrary/package_bgs/lb/BGModel.cpp \
    Detection/bgslibrary/package_bgs/lb/BGModelFuzzyGauss.cpp \
    Detection/bgslibrary/package_bgs/lb/BGModelFuzzySom.cpp \
    Detection/bgslibrary/package_bgs/lb/BGModelGauss.cpp \
    Detection/bgslibrary/package_bgs/lb/BGModelMog.cpp \
    Detection/bgslibrary/package_bgs/lb/BGModelSom.cpp \
    Detection/bgslibrary/package_bgs/LBP_MRF/graph.cpp \
    Detection/bgslibrary/package_bgs/LBP_MRF/maxflow.cpp \
    Detection/bgslibrary/package_bgs/LBP_MRF/MEDefs.cpp \
    Detection/bgslibrary/package_bgs/LBP_MRF/MEHistogram.cpp \
    Detection/bgslibrary/package_bgs/LBP_MRF/MEImage.cpp \
    Detection/bgslibrary/package_bgs/LBP_MRF/MotionDetection.cpp \
    Detection/bgslibrary/package_bgs/LBSP/BackgroundSubtractorLBSP.cpp \
    Detection/bgslibrary/package_bgs/LBSP/BackgroundSubtractorLBSP_.cpp \
    Detection/bgslibrary/package_bgs/LBSP/BackgroundSubtractorLOBSTER.cpp \
    Detection/bgslibrary/package_bgs/LBSP/BackgroundSubtractorPAWCS.cpp \
    Detection/bgslibrary/package_bgs/LBSP/BackgroundSubtractorSuBSENSE.cpp \
    Detection/bgslibrary/package_bgs/LBSP/LBSP.cpp \
    Detection/bgslibrary/package_bgs/LBSP/LBSP_.cpp \
    Detection/bgslibrary/package_bgs/MultiLayer/blob.cpp \
    Detection/bgslibrary/package_bgs/MultiLayer/BlobExtraction.cpp \
    Detection/bgslibrary/package_bgs/MultiLayer/BlobResult.cpp \
    Detection/bgslibrary/package_bgs/MultiLayer/CMultiLayerBGS.cpp \
    Detection/bgslibrary/package_bgs/MultiLayer/LocalBinaryPattern.cpp \
    Detection/bgslibrary/package_bgs/PBAS/PBAS.cpp \
    Detection/bgslibrary/package_bgs/SigmaDelta/sdLaMa091.cpp \
    Detection/bgslibrary/package_bgs/T2F/FuzzyUtils.cpp \
    Detection/bgslibrary/package_bgs/T2F/MRF.cpp \
    Detection/bgslibrary/package_bgs/T2F/T2FGMM.cpp \
    Detection/bgslibrary/package_bgs/T2F/T2FMRF.cpp \
    Detection/bgslibrary/package_bgs/TwoPoints/two_points.cpp \
    Detection/bgslibrary/package_bgs/ViBe/vibe-background-sequential.cpp \
    Detection/bgslibrary/package_bgs/VuMeter/TBackground.cpp \
    Detection/bgslibrary/package_bgs/VuMeter/TBackgroundVuMeter.cpp \
    Detection/bgslibrary/package_bgs/AdaptiveBackgroundLearning.cpp \
    Detection/bgslibrary/package_bgs/AdaptiveSelectiveBackgroundLearning.cpp \
    Detection/bgslibrary/package_bgs/CodeBook.cpp \
    Detection/bgslibrary/package_bgs/DPAdaptiveMedian.cpp \
    Detection/bgslibrary/package_bgs/DPEigenbackground.cpp \
    Detection/bgslibrary/package_bgs/DPGrimsonGMM.cpp \
    Detection/bgslibrary/package_bgs/DPMean.cpp \
    Detection/bgslibrary/package_bgs/DPPratiMediod.cpp \
    Detection/bgslibrary/package_bgs/DPTexture.cpp \
    Detection/bgslibrary/package_bgs/DPWrenGA.cpp \
    Detection/bgslibrary/package_bgs/DPZivkovicAGMM.cpp \
    Detection/bgslibrary/package_bgs/FrameDifference.cpp \
    Detection/bgslibrary/package_bgs/FuzzyChoquetIntegral.cpp \
    Detection/bgslibrary/package_bgs/FuzzySugenoIntegral.cpp \
    Detection/bgslibrary/package_bgs/GMG.cpp \
    Detection/bgslibrary/package_bgs/IndependentMultimodal.cpp \
    Detection/bgslibrary/package_bgs/KDE.cpp \
    Detection/bgslibrary/package_bgs/KNN.cpp \
    Detection/bgslibrary/package_bgs/LBAdaptiveSOM.cpp \
    Detection/bgslibrary/package_bgs/LBFuzzyAdaptiveSOM.cpp \
    Detection/bgslibrary/package_bgs/LBFuzzyGaussian.cpp \
    Detection/bgslibrary/package_bgs/LBMixtureOfGaussians.cpp \
    Detection/bgslibrary/package_bgs/LBP_MRF.cpp \
    Detection/bgslibrary/package_bgs/LBSimpleGaussian.cpp \
    Detection/bgslibrary/package_bgs/LOBSTER.cpp \
    Detection/bgslibrary/package_bgs/MixtureOfGaussianV1.cpp \
    Detection/bgslibrary/package_bgs/MixtureOfGaussianV2.cpp \
    Detection/bgslibrary/package_bgs/MultiCue.cpp \
    Detection/bgslibrary/package_bgs/MultiLayer.cpp \
    Detection/bgslibrary/package_bgs/PAWCS.cpp \
    Detection/bgslibrary/package_bgs/PixelBasedAdaptiveSegmenter.cpp \
    Detection/bgslibrary/package_bgs/SigmaDelta.cpp \
    Detection/bgslibrary/package_bgs/StaticFrameDifference.cpp \
    Detection/bgslibrary/package_bgs/SuBSENSE.cpp \
    Detection/bgslibrary/package_bgs/T2FGMM_UM.cpp \
    Detection/bgslibrary/package_bgs/T2FGMM_UV.cpp \
    Detection/bgslibrary/package_bgs/T2FMRF_UM.cpp \
    Detection/bgslibrary/package_bgs/T2FMRF_UV.cpp \
    Detection/bgslibrary/package_bgs/TwoPoints.cpp \
    Detection/bgslibrary/package_bgs/ViBe.cpp \
    Detection/bgslibrary/package_bgs/VuMeter.cpp \
    Detection/bgslibrary/package_bgs/WeightedMovingMean.cpp \
    Detection/bgslibrary/package_bgs/WeightedMovingVariance.cpp \
    Tracking/tracking.cpp \
    Tracking/LocalTracker.cpp \
    Tracking/Kalman.cpp \
    Tracking/HungarianAlg.cpp \
    SpeedEstimation/speedestimation.cpp \
    Display/display.cpp \
    InfractionDetection/infractiondetection.cpp \
    Classification/classification.cpp \
    Recognition/recognition.cpp \
    Buffer/infractionproofmaker.cpp


HEADERS += \
        mainwindow.h \
    Buffer/buffer.h \
    Buffer/frame.h \
    Buffer/vehicle.h \
    Buffer/configscene.h \
    Buffer/imageindexed.h \
    Buffer/vehicleblob.h \
    Buffer/infraction.h \
    Buffer/region.h \
    Buffer/trafficsignalregion.h \
    Acquisition/acquisition.h \
    Preprocessing/preprocessing.h \
    Detection/detection.h \
    Detection/bgslibrary/package_analysis/ForegroundMaskAnalysis.h \
    Detection/bgslibrary/package_analysis/PerformanceUtils.h \
    Detection/bgslibrary/package_analysis/PixelUtils.h \
    Detection/bgslibrary/package_bgs/_template_/amber/amber.h \
    Detection/bgslibrary/package_bgs/_template_/Amber.h \
    Detection/bgslibrary/package_bgs/_template_/MyBGS.h \
    Detection/bgslibrary/package_bgs/dp/AdaptiveMedianBGS.h \
    Detection/bgslibrary/package_bgs/dp/Bgs.h \
    Detection/bgslibrary/package_bgs/dp/BgsParams.h \
    Detection/bgslibrary/package_bgs/dp/Eigenbackground.h \
    Detection/bgslibrary/package_bgs/dp/Error.h \
    Detection/bgslibrary/package_bgs/dp/GrimsonGMM.h \
    Detection/bgslibrary/package_bgs/dp/Image.h \
    Detection/bgslibrary/package_bgs/dp/MeanBGS.h \
    Detection/bgslibrary/package_bgs/dp/PratiMediodBGS.h \
    Detection/bgslibrary/package_bgs/dp/TextureBGS.h \
    Detection/bgslibrary/package_bgs/dp/WrenGA.h \
    Detection/bgslibrary/package_bgs/dp/ZivkovicAGMM.h \
    Detection/bgslibrary/package_bgs/IMBS/IMBS.hpp \
    Detection/bgslibrary/package_bgs/KDE/KernelTable.h \
    Detection/bgslibrary/package_bgs/KDE/NPBGmodel.h \
    Detection/bgslibrary/package_bgs/KDE/NPBGSubtractor.h \
    Detection/bgslibrary/package_bgs/lb/BGModel.h \
    Detection/bgslibrary/package_bgs/lb/BGModelFuzzyGauss.h \
    Detection/bgslibrary/package_bgs/lb/BGModelFuzzySom.h \
    Detection/bgslibrary/package_bgs/lb/BGModelGauss.h \
    Detection/bgslibrary/package_bgs/lb/BGModelMog.h \
    Detection/bgslibrary/package_bgs/lb/BGModelSom.h \
    Detection/bgslibrary/package_bgs/lb/Types.h \
    Detection/bgslibrary/package_bgs/LBP_MRF/block.h \
    Detection/bgslibrary/package_bgs/LBP_MRF/graph.h \
    Detection/bgslibrary/package_bgs/LBP_MRF/MEDefs.hpp \
    Detection/bgslibrary/package_bgs/LBP_MRF/MEHistogram.hpp \
    Detection/bgslibrary/package_bgs/LBP_MRF/MEImage.hpp \
    Detection/bgslibrary/package_bgs/LBP_MRF/MotionDetection.hpp \
    Detection/bgslibrary/package_bgs/LBSP/BackgroundSubtractorLBSP.h \
    Detection/bgslibrary/package_bgs/LBSP/BackgroundSubtractorLBSP_.h \
    Detection/bgslibrary/package_bgs/LBSP/BackgroundSubtractorLOBSTER.h \
    Detection/bgslibrary/package_bgs/LBSP/BackgroundSubtractorPAWCS.h \
    Detection/bgslibrary/package_bgs/LBSP/BackgroundSubtractorSuBSENSE.h \
    Detection/bgslibrary/package_bgs/LBSP/DistanceUtils.h \
    Detection/bgslibrary/package_bgs/LBSP/LBSP.h \
    Detection/bgslibrary/package_bgs/LBSP/LBSP_.h \
    Detection/bgslibrary/package_bgs/LBSP/RandUtils.h \
    Detection/bgslibrary/package_bgs/MultiLayer/BackgroundSubtractionAPI.h \
    Detection/bgslibrary/package_bgs/MultiLayer/BGS.h \
    Detection/bgslibrary/package_bgs/MultiLayer/blob.h \
    Detection/bgslibrary/package_bgs/MultiLayer/BlobExtraction.h \
    Detection/bgslibrary/package_bgs/MultiLayer/BlobLibraryConfiguration.h \
    Detection/bgslibrary/package_bgs/MultiLayer/BlobResult.h \
    Detection/bgslibrary/package_bgs/MultiLayer/CMultiLayerBGS.h \
    Detection/bgslibrary/package_bgs/MultiLayer/LocalBinaryPattern.h \
    Detection/bgslibrary/package_bgs/MultiLayer/OpenCvDataConversion.h \
    Detection/bgslibrary/package_bgs/MultiLayer/OpenCvLegacyIncludes.h \
    Detection/bgslibrary/package_bgs/PBAS/PBAS.h \
    Detection/bgslibrary/package_bgs/SigmaDelta/sdLaMa091.h \
    Detection/bgslibrary/package_bgs/T2F/FuzzyUtils.h \
    Detection/bgslibrary/package_bgs/T2F/MRF.h \
    Detection/bgslibrary/package_bgs/T2F/T2FGMM.h \
    Detection/bgslibrary/package_bgs/T2F/T2FMRF.h \
    Detection/bgslibrary/package_bgs/TwoPoints/two_points.h \
    Detection/bgslibrary/package_bgs/ViBe/vibe-background-sequential.h \
    Detection/bgslibrary/package_bgs/VuMeter/TBackground.h \
    Detection/bgslibrary/package_bgs/VuMeter/TBackgroundVuMeter.h \
    Detection/bgslibrary/package_bgs/AdaptiveBackgroundLearning.h \
    Detection/bgslibrary/package_bgs/AdaptiveSelectiveBackgroundLearning.h \
    Detection/bgslibrary/package_bgs/bgslibrary.h \
    Detection/bgslibrary/package_bgs/CodeBook.h \
    Detection/bgslibrary/package_bgs/DPAdaptiveMedian.h \
    Detection/bgslibrary/package_bgs/DPEigenbackground.h \
    Detection/bgslibrary/package_bgs/DPGrimsonGMM.h \
    Detection/bgslibrary/package_bgs/DPMean.h \
    Detection/bgslibrary/package_bgs/DPPratiMediod.h \
    Detection/bgslibrary/package_bgs/DPTexture.h \
    Detection/bgslibrary/package_bgs/DPWrenGA.h \
    Detection/bgslibrary/package_bgs/DPZivkovicAGMM.h \
    Detection/bgslibrary/package_bgs/FrameDifference.h \
    Detection/bgslibrary/package_bgs/FuzzyChoquetIntegral.h \
    Detection/bgslibrary/package_bgs/FuzzySugenoIntegral.h \
    Detection/bgslibrary/package_bgs/GMG.h \
    Detection/bgslibrary/package_bgs/IBGS.h \
    Detection/bgslibrary/package_bgs/IndependentMultimodal.h \
    Detection/bgslibrary/package_bgs/KDE.h \
    Detection/bgslibrary/package_bgs/KNN.h \
    Detection/bgslibrary/package_bgs/LBAdaptiveSOM.h \
    Detection/bgslibrary/package_bgs/LBFuzzyAdaptiveSOM.h \
    Detection/bgslibrary/package_bgs/LBFuzzyGaussian.h \
    Detection/bgslibrary/package_bgs/LBMixtureOfGaussians.h \
    Detection/bgslibrary/package_bgs/LBP_MRF.h \
    Detection/bgslibrary/package_bgs/LBSimpleGaussian.h \
    Detection/bgslibrary/package_bgs/LOBSTER.h \
    Detection/bgslibrary/package_bgs/MixtureOfGaussianV1.h \
    Detection/bgslibrary/package_bgs/MixtureOfGaussianV2.h \
    Detection/bgslibrary/package_bgs/MultiCue.h \
    Detection/bgslibrary/package_bgs/MultiLayer.h \
    Detection/bgslibrary/package_bgs/PAWCS.h \
    Detection/bgslibrary/package_bgs/PixelBasedAdaptiveSegmenter.h \
    Detection/bgslibrary/package_bgs/SigmaDelta.h \
    Detection/bgslibrary/package_bgs/StaticFrameDifference.h \
    Detection/bgslibrary/package_bgs/SuBSENSE.h \
    Detection/bgslibrary/package_bgs/T2FGMM_UM.h \
    Detection/bgslibrary/package_bgs/T2FGMM_UV.h \
    Detection/bgslibrary/package_bgs/T2FMRF_UM.h \
    Detection/bgslibrary/package_bgs/T2FMRF_UV.h \
    Detection/bgslibrary/package_bgs/TwoPoints.h \
    Detection/bgslibrary/package_bgs/ViBe.h \
    Detection/bgslibrary/package_bgs/VuMeter.h \
    Detection/bgslibrary/package_bgs/WeightedMovingMean.h \
    Detection/bgslibrary/package_bgs/WeightedMovingVariance.h \
    Tracking/tracking.h \
    Tracking/track.h \
    Tracking/LocalTracker.h \
    Tracking/Kalman.h \
    Tracking/HungarianAlg.h \
    Tracking/defines.h \
    SpeedEstimation/speedestimation.h \
    Display/display.h \
    InfractionDetection/infractiondetection.h \
    Classification/classification.h \
    Recognition/recognition.h \
    Buffer/infractionproofmaker.h


FORMS += mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


LIBS += `pkg-config --libs opencv`
INCLUDEPATH += '/usr/local/include'
