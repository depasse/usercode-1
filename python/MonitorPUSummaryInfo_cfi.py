import FWCore.ParameterSet.Config as cms

monitorPUSummaryInfo = cms.EDAnalyzer("MonitorPUSummaryInfo",
    puSummaryCollection = cms.InputTag("addPileupInfo"),
)                                
