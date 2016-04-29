import warnings
warnings.warn('ATTENTION: This job uses Run 1 Geometry.')

import FWCore.ParameterSet.Config as cms

#
# Geometry master configuration
#
# Ideal geometry, needed for simulation
#from Geometry.CMSCommonData.cmsExtendedGeometryXML_cfi import *

from Geometry.CMSCommonData.cmsExtendedGeometry2016XML_RP_CTPPS_cfi import *
from Geometry.TrackerNumberingBuilder.trackerNumberingGeometry_cfi import *

