import FWCore.ParameterSet.Config as cms

testGenInfoProduct = cms.EDAnalyzer("TestGenInfoProduct",
    genrunCollection = cms.InputTag("generator"),
    genevtCollection = cms.InputTag("generator")
)                    
