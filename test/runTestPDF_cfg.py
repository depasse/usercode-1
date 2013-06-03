import FWCore.ParameterSet.Config as cms

process = cms.Process("runTestPDF")
process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:step1.root')
)


# Produce PDF weights (maximum is 3) note that it needs to be enabled in the path if you want weights
process.pdfWeights = cms.EDProducer("PdfWeightProducer",
#      GenTag = cms.untracked.InputTag("prunedGenParticles"),
      PdfInfoTag = cms.untracked.InputTag("generator"),
      PdfSetNames = cms.untracked.vstring(
              "MSTW2008lo68cl.LHgrid"
              #,"cteq6ll.LHpdf"
      )
)


process.load("usercode.fabiocos.testPDF_cfi")

#take the PDF from the generated events
process.testPDF.genCollection = cms.InputTag("generator")
process.testPDF.PdfWeightProd = cms.string("pdfWeights")
process.testPDF.PdfSetName = cms.string("MSTW2008lo68cl.LHgrid")


process.MessageLogger.categories=cms.untracked.vstring('FwkJob'
                                                      ,'FwkReport'
                                                      ,'FwkSummary'
                                                      ,'Root_NoDictionary'
                                                      ,'TestPDFInfo'
)
    

process.MessageLogger.cerr.INFO = cms.untracked.PSet(limit = cms.untracked.int32(-1))
process.MessageLogger.cerr.TestPDFInfo = cms.untracked.PSet(limit = cms.untracked.int32(-1))
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(10000)

process.TFileService = cms.Service("TFileService", fileName = cms.string("runTestPDF_histo.root") )



# Get event info
#process.load("FWCore.Modules.printContent_cfi")



process.p = cms.Path(
      process.pdfWeights*
      #process.printContent*
      process.testPDF
)
