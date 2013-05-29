import FWCore.ParameterSet.Config as cms

ecalMinBiasAnalysis = cms.EDAnalyzer("EcalMinBiasAnalysis",
    recoVertexCollection = cms.InputTag("offlinePrimaryVertices"),
    pixelClusterCollection = cms.InputTag("siPixelClusters"),
    ebRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEB"),                                     
    eeRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
    eeDigiCollection = cms.InputTag("ecalDigis","eeDigis"),
    vtxSel = cms.int32(20)                                     
)                                
