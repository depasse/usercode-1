import FWCore.ParameterSet.Config as cms

process = cms.Process("runMonitorPUSummaryInfo")
process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:pu_digi.root')
)

process.load("UserCode.fabiocos.MonitorCrossingFramePlaybackInfoExtended_cfi")

process.MessageLogger.categories=cms.untracked.vstring('FwkJob'
                                                      ,'FwkReport'
                                                      ,'FwkSummary'
                                                      ,'Root_NoDictionary'
                                                      ,'PUSummaryInfo'
)
    

process.p = cms.Path(process.monitorCrossingFramePlaybackInfoExtended)


