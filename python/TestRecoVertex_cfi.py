import FWCore.ParameterSet.Config as cms

testRecoVertex = cms.EDAnalyzer("TestRecoVertex",
    recoVertexCollection = cms.InputTag("offlinePrimaryVertices")                                
)                                
