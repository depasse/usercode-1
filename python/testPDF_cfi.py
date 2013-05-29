import FWCore.ParameterSet.Config as cms

testPDF = cms.EDAnalyzer("TestPDF",
    genCollection = cms.InputTag("generator"),
    pdfWeightProd = cms.string("PdfWeightProd"),
    pdfSetName = cms.string("CTEQ6L1")
)                    
