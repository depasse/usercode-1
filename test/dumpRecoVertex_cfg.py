import FWCore.ParameterSet.Config as cms

process = cms.Process("dumpRecoVertex")
process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:reco.root')
)

process.load("usercode.fabiocos.TestRecoVertex_cfi")

process.p = cms.Path(process.testRecoVertex)


