import FWCore.ParameterSet.Config as cms

monitorCrossingFramePlaybackInfoExtended = cms.EDAnalyzer("MonitorCrossingFramePlaybackInfoExtended",
    puSummaryCollection = cms.InputTag("mix"),
    nSource = cms.uint32(1),                                                      
    nBX = cms.uint32(3),
    minBunch = cms.int32(-1)                                                      
)                                
