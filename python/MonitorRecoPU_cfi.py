import FWCore.ParameterSet.Config as cms

monitorRecoPU = cms.EDAnalyzer("MonitorRecoPU",
    recoVertexCollection = cms.InputTag("offlinePrimaryVertices"),
    pixelClusterCollection = cms.InputTag("siPixelClusters")
)                                
