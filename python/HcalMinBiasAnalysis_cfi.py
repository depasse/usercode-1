import FWCore.ParameterSet.Config as cms

hcalMinBiasAnalysis = cms.EDAnalyzer("HcalMinBiasAnalysis",
    recoVertexCollection = cms.InputTag("offlinePrimaryVertices"),
    hbheRecHitCollection = cms.InputTag("hbhereco"),
    vtxSel = cms.int32(20)                                     
)                                
