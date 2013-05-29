import FWCore.ParameterSet.Config as cms

process = cms.Process("testGaussianZBeamSpotFilter")
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.load("IOMC.RandomEngine.IOMC_cff")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:gen.root')
)

process.load("IOMC.EventVertexGenerators.GaussianZBeamSpotFilter_cfi")

process.vtxFilterTest = cms.EDAnalyzer("SimPVMonitor",
    src = cms.InputTag("generator")
)

process.TFileService = cms.Service("TFileService", fileName = cms.string("testGaussianZBeamSpotFilter_histo.root") )

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

process.p = cms.Path(process.simBeamSpotFilter*process.vtxFilterTest)
#process.p = cms.Path(process.vtxFilterTest)


