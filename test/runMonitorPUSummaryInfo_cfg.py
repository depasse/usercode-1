import FWCore.ParameterSet.Config as cms

process = cms.Process("runMonitorPUSummaryInfo")
process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:pu_digi.root')
)

process.load("UserCode.fabiocos.MonitorPUSummaryInfo_cfi")

process.MessageLogger.categories=cms.untracked.vstring('FwkJob'
                                                      ,'FwkReport'
                                                      ,'FwkSummary'
                                                      ,'Root_NoDictionary'
                                                      ,'PUSummaryInfo'
)
    

process.MessageLogger.cerr.INFO = cms.untracked.PSet(limit = cms.untracked.int32(-1))
process.MessageLogger.cerr.PUSummaryInfo = cms.untracked.PSet(limit = cms.untracked.int32(-1))
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(10000)

process.TFileService = cms.Service("TFileService", fileName = cms.string("monitorPUSummaryInfo_histo.root") )

process.p = cms.Path(process.monitorPUSummaryInfo)


