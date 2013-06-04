import FWCore.ParameterSet.Config as cms

stdCTAnaPset = cms.PSet(
    recoVertexCollection = cms.InputTag("offlinePrimaryVertices"),
    caloTowerCollection = cms.InputTag("towerMaker"),
    vtxSel = cms.int32(20),
    etTh = cms.double(1.),
    etEmTh = cms.double(0.),
    etHadTh = cms.double(0.)                                   
)

caloTowerAnalysis = cms.EDAnalyzer("CaloTowerAnalysis",
    stdCTAnaPset
)                                
