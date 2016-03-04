# example config, copied from /afs/cern.ch/work/t/totemprd/totem/test_leszek/reco_run9510/workspace/totcsi_rec01/run1/parallel1/submission_files

import FWCore.ParameterSet.Config as cms

process = cms.Process("9510")
process.maxEvents = cms.untracked.PSet(
input = cms.untracked.int32(10)
)

process.load('TotemRawDataLibrary.Readers.RawDataSource_cfi')
process.source.fileNames = cms.untracked.vstring()

# TODO change input files here run_9881_EVB13_1.000
process.source.fileNames.append('/afs/cern.ch/work/p/polme/public/totemdata/run_9881_EVB13_1.000.srs')
#process.source.fileNames.append('root://eostotem//eos/totem/data/rawdata/2015/run_EVB12_9417.000.srs')

# Should review these config file
process.load("Configuration.TotemCommon.LoggerMin_cfi") # cmssw_7_0
#process.load("Configuration.TotemCommon.geometryGlobal_cfi") # cmssw_7_0
process.load("Configuration.TotemCommon.geometryRP_PPS_cfi") 


# TODO - check RP distances, check if commited to repository
#It is not there
#process.XMLIdealGeometryESSource.geomXMLFiles.append("Geometry/TotemRPData/data/2015_08_25_fill4269_2/RP_Dist_Beam_Cent.xml")

process.XMLIdealGeometryESSource.geomXMLFiles.append("Geometry/TotemRPData/data/2013_02_14/RP_Dist_Beam_Cent.xml")



# TODO - check RP alignement, check if commited to repository
process.load("TotemAlignment.RPDataFormats.TotemRPIncludeAlignments_cfi")
# It is not there
#process.TotemRPIncludeAlignments.RealFiles = cms.vstring(
#"TotemAlignment/RPData/alignment_tb_run9509_45_no20.xml",
#"TotemAlignment/RPData/alignment_tb_run9509_56.xml"
#)

# TODO - check if optics commited to repository
#It is not there
#process.load("Configuration.TotemOpticsConfiguration.OpticsConfig_6500GeV_19p2_cfi") 
process.load("Configuration.TotemOpticsConfiguration.OpticsConfig_6500GeV_90_cfi")

process.load('TotemCondFormats.DAQInformation.DAQMappingSourceXML_cfi')
process.DAQMappingSourceXML.mappingFileNames.append('TotemCondFormats/DAQInformation/data/rp_220_210far.xml')
process.DAQMappingSourceXML.mappingFileNames.append('TotemCondFormats/DAQInformation/data/t1_all_run2.xml')
process.DAQMappingSourceXML.mappingFileNames.append('TotemCondFormats/DAQInformation/data/t2_3quarters.xml')
process.DAQMappingSourceXML.maskFileNames.append('TotemCondFormats/DAQInformation/test/T1DeadChannelsList_9255_onlyStrips.xml')

process.load("Configuration.TotemCommon.RandomNumbers_cfi")

process.load('TotemRawDataLibrary.RawToDigi.Raw2DigiProducer_cfi')
process.Raw2DigiProducer.rpDataProductLabel = cms.untracked.string("")
process.Raw2DigiProducer.rpCCProductLabel = cms.untracked.string("")

process.TriggerBits = cms.EDProducer("RPTriggerBitsProducer",verbose = cms.bool(False))
process.TriggerBits.StripDigiLabel = cms.InputTag("Raw2DigiProducer")

process.load("RecoTotemRP.RPClusterizer.RPClusterizationConf_cfi")
process.RPClustProd.DigiLabel = cms.InputTag("Raw2DigiProducer")
process.load("RecoTotemRP.RPRecoHitProducer.RPRecoHitProdConf_cfi")
process.load("RecoTotemRP.RPSingleCandidateTrackFinder.RPSingleTrackCandFindConf_cfi")

#process.load("RecoTotemRP.RPNonParallelTrackCandidateFinder.RPNonParallelTrackCandidateFinder_cfi")
process.load("RecoTotemRP.RPTrackCandidateCollectionFitter.RPSingleTrackCandCollFitted_cfi")
process.RPSingleTrackCandCollFit.RPTrackCandCollProducer = 'NonParallelTrackFinder'
#process.load("RecoTotemRP.RPMulTrackCandidateCollectionFitter.RPMulTrackNonParallelRecoFitter_cfi")

#process.load("L1TriggerTotem.CoincidenceChip.RPCoincidenceProducer_cfi")
#process.RPCC.DetTriggerLabel = cms.InputTag("TriggerBits")

# TODO - check if reconstruction settings commited to repository
# it is not there
#process.load("RecoTotemRP.RPInelasticReconstruction.RPRec220_19p2_cfi")
process.load("RecoTotemRP.RPInelasticReconstruction.RPRec220_cfi")
process.RP220Reconst.BeamProtTransportSetup = process.BeamProtTransportSetup

process.output = cms.OutputModule(
"PoolOutputModule",
fileName = cms.untracked.string("file:./out.root"),
outputCommands = cms.untracked.vstring('keep *')
)

process.path = cms.Path(
process.Raw2DigiProducer
#*process.TriggerBits
*process.RPClustProd
*process.RPRecoHitProd
*process.RPSinglTrackCandFind
#*process.NonParallelTrackFinder
*process.RPSingleTrackCandCollFit
#*process.RPMulTrackNonParallelCandCollFit
*process.RP220Reconst
)

process.outpath = cms.EndPath(process.output)