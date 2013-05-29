import FWCore.ParameterSet.Config as cms

process = cms.Process("runTestGenInfoProduct")
process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:gen.root')
)

process.load("UserCode.fabiocos.testGenInfoProduct_cfi")

process.p = cms.Path(process.testGenInfoProduct)
