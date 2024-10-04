#include "TROOT.h"
#include "TH1.h"
#include "TTree.h"
#include "TH2.h"
#include "TAxis.h"
#include "TF1.h"
#include "TFile.h"
#include "TMath.h"
#include "TSystem.h"
#include "TVector2.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TRandom.h"
#include <iostream>
#include <fstream>
#include "TMath.h"
#include <phool/PHCompositeNode.h>
#include <fun4all/Fun4AllReturnCodes.h>
#include <pdbcalbase/PdbParameterMap.h>
#include <phool/PHCompositeNode.h>
#include <phool/PHTimeServer.h>
#include <phool/PHTimer.h>
#include <phool/getClass.h>

#include <fun4all/SubsysReco.h>

#include "HFMLRealData.h"

#include <g4detectors/PHG4Cell.h>
#include <g4detectors/PHG4CellContainer.h>
#include <g4detectors/PHG4CylinderCellGeom.h>
#include <g4detectors/PHG4CylinderCellGeomContainer.h>
#include <g4detectors/PHG4CylinderGeom.h>
#include <g4detectors/PHG4CylinderGeomContainer.h>




#include "/cvmfs/sphenix.sdcc.bnl.gov/gcc-8.3/opt/sphenix/core/rapidjson/include/rapidjson/allocators.h"
#include "/cvmfs/sphenix.sdcc.bnl.gov/gcc-8.3/opt/sphenix/core/rapidjson/include/rapidjson/cursorstreamwrapper.h"
#include "/cvmfs/sphenix.sdcc.bnl.gov/gcc-8.3/opt/sphenix/core/rapidjson/include/rapidjson/document.h"
#include "/cvmfs/sphenix.sdcc.bnl.gov/gcc-8.3/opt/sphenix/core/rapidjson/include/rapidjson/encodedstream.h"
#include "/cvmfs/sphenix.sdcc.bnl.gov/gcc-8.3/opt/sphenix/core/rapidjson/include/rapidjson/encodings.h"
#include "/cvmfs/sphenix.sdcc.bnl.gov/gcc-8.3/opt/sphenix/core/rapidjson/include/rapidjson/filereadstream.h"
#include "/cvmfs/sphenix.sdcc.bnl.gov/gcc-8.3/opt/sphenix/core/rapidjson/include/rapidjson/filewritestream.h"
#include "/cvmfs/sphenix.sdcc.bnl.gov/gcc-8.3/opt/sphenix/core/rapidjson/include/rapidjson/fwd.h"
#include "/cvmfs/sphenix.sdcc.bnl.gov/gcc-8.3/opt/sphenix/core/rapidjson/include/rapidjson/istreamwrapper.h"
#include "/cvmfs/sphenix.sdcc.bnl.gov/gcc-8.3/opt/sphenix/core/rapidjson/include/rapidjson/memorybuffer.h"
#include "/cvmfs/sphenix.sdcc.bnl.gov/gcc-8.3/opt/sphenix/core/rapidjson/include/rapidjson/memorystream.h"
#include "/cvmfs/sphenix.sdcc.bnl.gov/gcc-8.3/opt/sphenix/core/rapidjson/include/rapidjson/ostreamwrapper.h"
#include "/cvmfs/sphenix.sdcc.bnl.gov/gcc-8.3/opt/sphenix/core/rapidjson/include/rapidjson/pointer.h"
#include "/cvmfs/sphenix.sdcc.bnl.gov/gcc-8.3/opt/sphenix/core/rapidjson/include/rapidjson/prettywriter.h"
#include "/cvmfs/sphenix.sdcc.bnl.gov/gcc-8.3/opt/sphenix/core/rapidjson/include/rapidjson/rapidjson.h"
#include "/cvmfs/sphenix.sdcc.bnl.gov/gcc-8.3/opt/sphenix/core/rapidjson/include/rapidjson/reader.h"
#include "/cvmfs/sphenix.sdcc.bnl.gov/gcc-8.3/opt/sphenix/core/rapidjson/include/rapidjson/schema.h"
#include "/cvmfs/sphenix.sdcc.bnl.gov/gcc-8.3/opt/sphenix/core/rapidjson/include/rapidjson/stream.h"
#include "/cvmfs/sphenix.sdcc.bnl.gov/gcc-8.3/opt/sphenix/core/rapidjson/include/rapidjson/stringbuffer.h"
#include "/cvmfs/sphenix.sdcc.bnl.gov/gcc-8.3/opt/sphenix/core/rapidjson/include/rapidjson/writer.h"


#include <boost/format.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>


#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <stdlib.h>

#include <mvtx/CylinderGeom_Mvtx.h>
#include <trackbase/MvtxDefs.h>
#include <intt/CylinderGeomIntt.h>
#include <trackbase/InttDefs.h>


#include <trackbase/TrkrHitSetContainer.h>
#include <trackbase/TrkrClusterContainer.h>
#include <trackbase_historic/TrackSeedContainer.h>



using namespace std;

using std::cout;
using std::endl;

//QA Added

TFile * DebugFile;
TTree *RawHitTree;



std::vector<int> INTTTimeBucketVec;
std::vector<float> SiHitX;
std::vector<float> SiHitY;
std::vector<float> SiHitZ;


float PVx;
float PVy;
float PVz;



int HitSize;
int MVTXHitSize;
int EvtID;
int INTTHitSize;
int NTruthTrks;




HFMLRealData::HFMLRealData(std::string filename)
	: SubsysReco("HFMLRealData"){
		std::cout << "Using - HFML Data DST -> JSON -> New -> ZZed" << std::endl;
	}

int HFMLRealData::Init(PHCompositeNode* topNode)
{

	std::cout << "Initiate HFML Real Data Task - Init -> Modi" << std::endl;
	Event = 0;
	EvtID = 0;
	DebugFile = new TFile("DebugFile.root","RECREATE");

	DebugFile->cd();

	RawHitTree = new TTree("RawHitTree","RawHitTree");
	RawHitTree->Branch("EvtID",&EvtID,"EvtID/I");
	RawHitTree->Branch("MVTXHitSize",&MVTXHitSize);


	RawHitTree->Branch("INTTHitSize",&INTTHitSize,"INTTHitSize/I");
	RawHitTree->Branch("HitSize",&HitSize,"HitSize/I");
	//	RawHitTree->Branch("CrossingID",&CrossingID);	
	RawHitTree->Branch("SiHitX",&SiHitX);
	RawHitTree->Branch("SiHitY",&SiHitY);
	RawHitTree->Branch("SiHitZ",&SiHitZ);


	m_jsonOut.open(_foutname, fstream::out);

	m_jsonOut << "{" << endl;
	m_jsonOut << "\"Events\" : [" << endl;

	//	m_hitsets = findNode::getClass<TrkrHitSetContainer>(topNode, "TRKR_HITSET");
	return Fun4AllReturnCodes::EVENT_OK;

}


int HFMLRealData::InitRun(PHCompositeNode* topNode)
{

	std::cout << "Initiate HFML Real Data Task - InitRun -> Modi" << std::endl;

	m_Geoms =
		findNode::getClass<PHG4CylinderGeomContainer>(topNode, "CYLINDERGEOM_MVTX");
	if (!m_Geoms)
	{
		//std::cout << PHWHERE << "ERROR: Can't find node CYLINDERCELLGEOM_MVTX" << std::endl;
		return Fun4AllReturnCodes::ABORTRUN;
	}

	m_Geoms2 =
		findNode::getClass<PHG4CylinderGeomContainer>(topNode, "CYLINDERGEOM_INTT");
	if (!m_Geoms2)
	{
		//std::cout << PHWHERE << "ERROR: Can't find node CYLINDERCELLGEOM_INTT" << std::endl;
		return Fun4AllReturnCodes::ABORTRUN;
	}
	actsGeom = findNode::getClass<ActsGeometry>(topNode, "ActsGeometry");
	if (!actsGeom)
	{
		cout << "HFMLTriggerInterface::InitRun - WARNING - missing actsGeom" << endl;
	}

	return Fun4AllReturnCodes::EVENT_OK;

}




int HFMLRealData::process_event(PHCompositeNode * topNode)
{


	
    TrkrClusterCrossingAssocv1 *trkrContainerCrossing = findNode::getClass<TrkrClusterCrossingAssocv1>(topNode, "TRKR_CLUSTERCROSSINGASSOC");

    if(!trkrContainerCrossing)
    {
      std::cout << "trkrContainerCrossing not found! Aborting!" << std::endl;
      return Fun4AllReturnCodes::ABORTEVENT;
    }


	auto res = load_nodes(topNode);
	//	cout << "ROCK - Runed bro - Pass 1.2 " << endl;

	if (res != Fun4AllReturnCodes::EVENT_OK)	return res;

	//	cout << "Running Event: " << Event << endl;


	MVTXHitSize = 0;
	INTTHitSize = 0;
	HitSize = 0;
	rapidjson::Document d;

	d.SetObject();
	rapidjson::Document::AllocatorType& alloc = d.GetAllocator();

	auto loadCoordinate = [&](double x, double y, double z) {
		//    ptree vertexTree;
		rapidjson::Value vertexTree(rapidjson::kArrayType);

		vertexTree.PushBack(x, alloc).PushBack(y, alloc).PushBack(z, alloc);

		return vertexTree;
	};

	//cout << "Pass 2" << endl;


	rapidjson::Value metaTree(rapidjson::kObjectType);
	metaTree.AddMember("Description", "These are meta data for this event. Not intended to use in ML algorithm", alloc);
	metaTree.AddMember("EventID", EvtID, alloc);
	metaTree.AddMember("Unit", "cm", alloc);

	rapidjson::Value rawHitTree(rapidjson::kObjectType);
	rawHitTree.AddMember("Description","This is Real sPHENIX Silicon Detector Data in p + p 200 GeV taken in Run 2024 for sPHENIX",alloc);
	rapidjson::Value rawHitsTree(rapidjson::kArrayType);

	//cout << "Pass 3" << endl;

	auto hitset_range = m_hitsets->getHitSets(TrkrDefs::TrkrId::mvtxId);
	//cout << "Pass 3.2" << endl;

	hitID = 0;

	for (auto hitset_iter =  hitset_range.first; hitset_iter != hitset_range.second; ++hitset_iter)
	{
		auto hitsetkey = hitset_iter->first;
		auto hit_range = hitset_iter->second->getHits();
		for (auto hit_iter = hit_range.first;
				hit_iter != hit_range.second;
				++hit_iter)
		{
			auto hitkey = hit_iter->first;
			auto hit = hit_iter->second;
			assert(hit);
			// get truth hit assoc


			//cout << "Pass 3.3" << endl;


			unsigned int layer = TrkrDefs::getLayer(hitset_iter->first);
			if (layer < _nlayers_maps)
			{
				CylinderGeom_Mvtx* geom = dynamic_cast<CylinderGeom_Mvtx*>(m_Geoms->GetLayerGeom(layer));
				assert(geom);

				unsigned int pixel_x = MvtxDefs::getRow(hitkey);
				unsigned int pixel_z = MvtxDefs::getCol(hitkey);
				assert((int)pixel_x < geom->get_NX());
				assert((int)pixel_z < geom->get_NZ());
				unsigned int chip = MvtxDefs::getChipId(hitsetkey);
				unsigned int stave = MvtxDefs::getStaveId(hitsetkey);
				auto surface = actsGeom->maps().getSiliconSurface(hitsetkey);


				//cout << "hitsetkey = " << hitsetkey << "     chip = " << chip << "    stave = " << stave << "    layer = " << layer << endl;
				TVector3 local_coords = geom->get_local_coords_from_pixel(pixel_x, pixel_z);

				//Add Surface and Act Maps Properties

				//cout << "Pass 3.4" << endl;

				TVector2 LocalUse;
				LocalUse.SetX(local_coords.x());
				LocalUse.SetY(local_coords.z());

				TVector3 world_coords = geom->get_world_from_local_coords(surface, actsGeom ,LocalUse);


				rapidjson::Value hitTree(rapidjson::kObjectType);

				//      ptree hitIDTree;
				rapidjson::Value hitIDTree(rapidjson::kObjectType);
				hitIDTree.AddMember("HitSequenceInEvent", hitID, alloc);
				//	hitIDTree.AddMember("MVTXTrkID", trkid, alloc);
				//	hitIDTree.AddMember("MVTXHitTime", MVTXHitTime, alloc);

				hitIDTree.AddMember("Layer", layer, alloc);
				hitIDTree.AddMember("Stave", stave, alloc);
				hitIDTree.AddMember("Chip", chip, alloc);
				hitIDTree.AddMember("Pixel_x", pixel_x, alloc);
				hitIDTree.AddMember("Pixel_z", pixel_z, alloc);
				hitTree.AddMember("ID", hitIDTree, alloc);

				double PixelGlobalX = world_coords.x();
				double PixelGlobalY = world_coords.y();
				double PixelGlobalZ = world_coords.z();

				hitTree.AddMember("Coordinate",
						loadCoordinate(PixelGlobalX,
							PixelGlobalY,
							PixelGlobalZ),
						alloc);


				hitTree.AddMember("ChipGlobalCoordinate",
						loadCoordinate(world_coords.x(),
							world_coords.y(),
							world_coords.z()),
						alloc);

				hitTree.AddMember("PixelLocalCoordinate",
						loadCoordinate(local_coords.x(),
							local_coords.y(),
							local_coords.z()),
						alloc);


				//cout << "Pass 3.7" << endl;



				INTTTimeBucketVec.push_back(0);


				SiHitX.push_back(world_coords.x() );
				SiHitY.push_back(world_coords.y() );
				SiHitZ.push_back(world_coords.z() );

				rawHitsTree.PushBack(hitTree, alloc);
				hitID++;
				MVTXHitSize = MVTXHitSize + 1;
				HitSize = HitSize + 1;
			}  //    if (layer < _nlayers_maps)
		}  //   for (TrkrHitSetContainer::ConstIterator hitset_iter = hitset_range.first;
	}  //   for (TrkrHitSet::ConstIterator hit_iter = hit_range.first;

	//cout << "Pass 4" << endl;

	rawHitTree.AddMember("MVTXHits", rawHitsTree, alloc);


	rapidjson::Value rawHitsTree2(rapidjson::kArrayType);



	INTTHitSize = 0;

	hitIDINTT = 0;

	////      cout << "Pass 1 new" << endl;
	//	auto clus_range = m_clus->getHitSets(TrkrDefs::TrkrId::inttId);
	auto hitset_range_intt = m_hitsets->getHitSets(TrkrDefs::TrkrId::inttId);

	for (TrkrHitSetContainer::ConstIterator hitset_iter = hitset_range_intt.first;
			hitset_iter != hitset_range_intt.second;
			++hitset_iter)
	{
		//	  TrkrDefs::hitsetkey hitSetKey = hitset_iter->first;
		auto hitsetkey = hitset_iter->first;

		//	std::cout << "hitsetkey = " << hitsetkey << std::endl;
		TrkrHitSet::ConstRange hit_range = hitset_iter->second->getHits();
		for (TrkrHitSet::ConstIterator hit_iter = hit_range.first;
				hit_iter != hit_range.second;
				++hit_iter)
		{

			//      cout << "Pass 1" << endl;
			TrkrDefs::hitkey hitKey = hit_iter->first;
			TrkrHit* hit = hit_iter->second;
			assert(hit);
			unsigned int layer = TrkrDefs::getLayer(hitset_iter->first);
			//	    cout << "Pass 2" << "   layer = " << layer  << endl;


			if(layer > _nlayers_maps-1){

				CylinderGeomIntt* geom = dynamic_cast<CylinderGeomIntt*>(m_Geoms2->GetLayerGeom(layer));
				//      cout << "Pass 3" << endl;


				unsigned int Row = InttDefs::getRow(hitKey);
				unsigned int Col = InttDefs::getCol(hitKey);
				unsigned int LadderZId = InttDefs::getLadderZId(hitsetkey);
				unsigned int LadderPhiId = InttDefs::getLadderPhiId(hitsetkey);
				double hit_location[3] = {0.0,0.0,0.0};

				int INTTTimeBucket = InttDefs::getTimeBucketId(hitKey);

				auto surface = actsGeom->maps().getSiliconSurface(hitsetkey);

				//			geom->find_strip_center_localcoords(LadderZId, Row, Col,location);



				//TVector3 world_coord =  get_world_from_local_coords(, hit_location)
				geom->find_strip_center(surface,actsGeom,LadderZId,LadderPhiId,Col,Row,hit_location);

				//geom->find_strip_center(surface, actsGeom, LadderZId, LadderPhiId, Row, Col, hit_location);

				//Use Surface for INTT too

				rapidjson::Value hitTree2(rapidjson::kObjectType);
				//      cout << "Pass 4" << endl;

				rapidjson::Value hitIDTree2(rapidjson::kObjectType);

				//int inttlayer = layer - _nlayers_maps;
				hitIDTree2.AddMember("HitSequenceInEvent", hitIDINTT, alloc);
				//		hitIDTree2.AddMember("G4HitAssoc", truthHitTree, alloc);	
				//	hitIDTree2.AddMember("INTTTrkID", trkid, alloc);
				//			hitIDTree2.AddMember("INTTHitTime", INTTHitTime, alloc);
				hitIDTree2.AddMember("INTTTimeBucket", INTTTimeBucket, alloc);

				hitIDTree2.AddMember("Layer", layer, alloc);
				hitIDTree2.AddMember("Row", Row, alloc);
				hitIDTree2.AddMember("Col", Col, alloc);
				hitIDTree2.AddMember("LadderZId", LadderZId, alloc);
				hitIDTree2.AddMember("LadderPhiId", LadderPhiId, alloc);

				//		cout << "Row: " << Row << endl;
				//hitIDTree2.AddMember("INTTCrossingID", hitIDINTT, alloc);


				hitTree2.AddMember("ID", hitIDTree2, alloc);
				hitTree2.AddMember("Coordinate",	loadCoordinate(hit_location[0], hit_location[1], hit_location[2]),	alloc);




				//cout << "Pass 4" << endl;
				rawHitsTree2.PushBack(hitTree2, alloc);


				//		rawHitTree.PushBack(hitTree2, alloc);

				//m_hitLayerMap->Fill(hit_location[0], hit_location[1], layer);

				INTTTimeBucketVec.push_back(INTTTimeBucket);

				SiHitX.push_back(hit_location[0]);
				SiHitY.push_back(hit_location[1]);
				SiHitZ.push_back(hit_location[2]);

				hitIDINTT++;
				INTTHitSize = INTTHitSize + 1;
				HitSize = HitSize + 1;

			}

			//      cout << "Pass 5" << endl;

		}

		//	INTTHITS = INTTHITS + 1;

	}


	rawHitTree.AddMember("INTTHits", rawHitsTree2, alloc);




	//rapidjson::Value sPHENIXRecoTree(rapidjson::kObjectType);
	//	rapidjson::Value sPHENIXRecoTree(rapidjson::kArrayType);
	//	auto hitset_range_intt = m_hitsets->getHitSets(TrkrDefs::TrkrId::inttId);




	rapidjson::Value sPHENIXRecoTree(rapidjson::kObjectType);
	sPHENIXRecoTree.AddMember("Description","This is what sPHENIX official tracking software reconstructed",alloc);

	rapidjson::Value EventGlobalTree(rapidjson::kArrayType);







	rapidjson::Value ClusTree(rapidjson::kArrayType);


	int clus_size = m_clus->size();
	int mvtx_clus_size = 0;
	int intt_clus_size = 0;

	int ClusID = 0;
	//int ClusType = -1;
	//auto hitset_range = m_hitsets->getHitSets(TrkrDefs::TrkrId::mvtxId);

	for (auto hitset_iter =  hitset_range.first; hitset_iter != hitset_range.second; ++hitset_iter)
	{


		auto hitsetkey = hitset_iter->first;


		auto range = m_clus->getClusters(hitsetkey);
		mvtx_clus_size = std::distance(range.first,range.second);


		for (auto iter = range.first; iter != range.second; ++iter)
		{

			auto cluskey = iter->first;
			auto cluster = iter->second;
			//	std::cout << "Inside clus" << std::endl;


			auto surface = actsGeom->maps().getSiliconSurface(cluskey);

			Acts::Vector3 global = actsGeom->getGlobalPosition(cluskey,cluster);  

			float clusx = global[0];
			float clusy = global[1];
			float clusz = global[2];




			rapidjson::Value clusTree2(rapidjson::kObjectType);

			clusTree2.AddMember("MVTXClusID", ClusID, alloc);
			//			   clusTree2.AddMember("ClusType", ClusType, alloc);

			clusTree2.AddMember("clusx", clusx, alloc);
			clusTree2.AddMember("clusy", clusy, alloc);
			clusTree2.AddMember("clusz", clusz, alloc);


			ClusTree.PushBack(clusTree2, alloc);

			ClusID++;


		}


	}

	//	auto hitset_range_intt = m_hitsets->getHitSets(TrkrDefs::TrkrId::inttId);


	int INTTClusID = 0; 

	for(TrkrHitSetContainer::ConstIterator hitset_iter = hitset_range_intt.first;
			hitset_iter != hitset_range_intt.second;
			++hitset_iter){
		//	  TrkrDefs::hitsetkey hitSetKey = hitset_iter->first;
		auto hitsetkey = hitset_iter->first;

		// get truth hit assoc




		auto range = m_clus->getClusters(hitsetkey);
		intt_clus_size = std::distance(range.first,range.second);


		for (auto iter = range.first; iter != range.second; ++iter)
		{

			auto cluskey = iter->first;
			auto cluster = iter->second;
			//	std::cout << "Inside clus" << std::endl;


			auto surface = actsGeom->maps().getSiliconSurface(cluskey);

			Acts::Vector3 global = actsGeom->getGlobalPosition(cluskey,cluster);  

			float clusx = global[0];
			float clusy = global[1];
			float clusz = global[2];


			int bunch_crossing_number = -1;
			TrkrClusterCrossingAssocv1::ConstRange bc_range = trkrContainerCrossing->getCrossings(cluskey);
			for(TrkrClusterCrossingAssocv1::ConstIterator bcIter = bc_range.first; bcIter != bc_range.second; ++bcIter)
			{
				if(bunch_crossing_number < 0) bunch_crossing_number = bcIter->second;
				if(bunch_crossing_number != bcIter->second)
				{
					bunch_crossing_number = -1;
					break;
				}
			}



			rapidjson::Value clusTree2(rapidjson::kObjectType);

			clusTree2.AddMember("INTTClusID", INTTClusID, alloc);
			//			   clusTree2.AddMember("ClusType", ClusType, alloc);
			clusTree2.AddMember("INTTBunchCrossing", bunch_crossing_number, alloc);

			clusTree2.AddMember("clusx", clusx, alloc);
			clusTree2.AddMember("clusy", clusy, alloc);
			clusTree2.AddMember("clusz", clusz, alloc);


			ClusTree.PushBack(clusTree2, alloc);

			INTTClusID++;


		}

	}




	//TrkrClusterContainer::ConstRange clusrange = m_clus->getClusters();

	//std::cout << "clusrange->size() = " << clusrange->size()  << std::endl;
	//std::cout << "But Still Passed" << std::endl;

	/*
	   for (TrkrClusterContainer::ConstIterator clusIter = clusrange.first; clusIter != clusrange.second; ++clusIter)
	   {


	   auto cluskey = clusIter->first;
	   auto cluster = clusIter->second;
	   std::cout << "Inside clus" << std::endl;


	   auto surface = actsGeom->maps().getSiliconSurface(cluskey);

	   Acts::Vector3 global = actsGeom->getGlobalPosition(cluskey,cluster);  

	   float clusx = global[0];
	   float clusy = global[1];
	   float clusz = global[2];




	   if(TrkrDefs::getTrkrId(cluskey) == TrkrDefs::mvtxId){

	   mvtx_clus_size++;
	   ClusType = 0;

	   }

	   if(TrkrDefs::getTrkrId(cluskey) == TrkrDefs::inttId){

	   intt_clus_size++;
	   ClusType = 1;

	   }



	   rapidjson::Value clusTree2(rapidjson::kObjectType);

	   clusTree2.AddMember("ClusID", ClusID, alloc);
	   clusTree2.AddMember("ClusType", ClusType, alloc);

	   clusTree2.AddMember("clusx", clusx, alloc);
	   clusTree2.AddMember("clusy", clusy, alloc);
	   clusTree2.AddMember("clusz", clusz, alloc);


	   ClusTree.PushBack(clusTree2, alloc);

	   ClusID++;

	   }
	   */

	//std::cout << "Pass 2" << std::endl;


	rapidjson::Value SeedTree(rapidjson::kArrayType);


	int SeedID = 0;

	TrackSeedContainer::ConstIter siseed_beg = m_si_seeds->begin();
	TrackSeedContainer::ConstIter siseed_end = m_si_seeds->end();


	int NTracklets = m_si_seeds->size();
	//std::cout << "Pass 3" << std::endl;


	for (TrackSeedContainer::ConstIter siseed_iter = siseed_beg; siseed_iter != siseed_end; ++siseed_iter)  //Looping through tracklets
	{
		//		std::cout << "Pass 3.1 -> Modi" << std::endl;

		int id = m_si_seeds->index(siseed_iter);
		TrackSeed *siseed = NULL;		
		siseed = m_si_seeds->get(id);
		//	std::cout << "Pass 3.2 -> Modi" << std::endl;


		if(!siseed){

			//			std::cout << "No Silicon Seed" << std::endl;
			continue;
		}else{

			//	TotalTracklets++;

		}



		float SeedPt = siseed->get_pt();
		float SeedEta = siseed->get_eta();
		int Crossing = siseed->get_crossing();
		int nmvtx = 0;
		int nintt = 0;

		TrackSeed::ClusterKeyIter cluskeybegin = siseed->begin_cluster_keys();
		TrackSeed::ClusterKeyIter cluskeyend = siseed->end_cluster_keys();
		//	std::cout << "Pass 3.3 -> Modi" << std::endl;

		for (TrackSeed::ClusterKeyIter cluskey = cluskeybegin; cluskey != cluskeyend; ++cluskey){ //looping through clusters


			if (TrkrDefs::getTrkrId(*cluskey) == TrkrDefs::inttId){
				nintt++;

			}

			if (TrkrDefs::getTrkrId(*cluskey) == TrkrDefs::mvtxId){
				nmvtx++;

			}

		}
		//	std::cout << "Pass 3.4 -> Modi" << std::endl;


		rapidjson::Value SiSeedTree(rapidjson::kObjectType);

		SiSeedTree.AddMember("SeedID", SeedID, alloc);
		SiSeedTree.AddMember("Crossing", Crossing, alloc);
		SiSeedTree.AddMember("nmvtx", nmvtx, alloc);
		SiSeedTree.AddMember("nintt", nintt, alloc);

		SiSeedTree.AddMember("SeedPt", SeedPt, alloc);
		SiSeedTree.AddMember("SeedEta", SeedEta, alloc);


		//	std::cout << "Pass 3.5 -> Modi" << std::endl;

		SeedTree.PushBack(SiSeedTree, alloc);

		SeedID++;
	}
	//	std::cout << "Pass 3.99" << std::endl;

	rapidjson::Value EvtTree(rapidjson::kObjectType);
	//	std::cout << "Pass 3.4" << std::endl;


	EvtTree.AddMember("EvtID", EvtID, alloc);
	EvtTree.AddMember("TotalSiClus", clus_size, alloc);
	EvtTree.AddMember("TotalMVTXClus", mvtx_clus_size, alloc);
	EvtTree.AddMember("TotalINTTClus", intt_clus_size, alloc);
	EvtTree.AddMember("TotalTracklets", NTracklets, alloc);

	//	std::cout << "Pass 3.7" << std::endl;

	EventGlobalTree.PushBack(EvtTree, alloc);


	//	sPHENIXRecoTree.PushBack(EvtTree, alloc);
	sPHENIXRecoTree.AddMember("EventGlobalTree", EventGlobalTree, alloc);
	sPHENIXRecoTree.AddMember("ClusTree", ClusTree, alloc);
	sPHENIXRecoTree.AddMember("SeedTree", SeedTree, alloc);


	d.AddMember("MetaData", metaTree, alloc);
	d.AddMember("RawHit", rawHitTree, alloc);
	//d.AddMember("TruthHit", truthHitTree, alloc);
	d.AddMember("sPHENIXRecoTree", sPHENIXRecoTree, alloc);

	assert(m_jsonOut.is_open());


	//	cout << "mvtx_clus_size = " << mvtx_clus_size << "   intt_clus_size = " << intt_clus_size << " clus_size =  " << clus_size << "   NTracklets = " << NTracklets << endl;
	if (EvtID > 0)
	{
		m_jsonOut << "," << endl;
	}
	rapidjson::OStreamWrapper osw(m_jsonOut);
	rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
	d.Accept(writer);


	//	std::cout << "Pass 4" << std::endl;



	RawHitTree->Fill();

	EvtID = EvtID + 1;
	cout << "Done Event" << endl;

	SiHitX.clear();
	SiHitY.clear();
	SiHitZ.clear();
	std::cout << "Pass 5" << std::endl;

	return Fun4AllReturnCodes::EVENT_OK;

}


int HFMLRealData::End(PHCompositeNode* topNode)
{

	DebugFile->cd();
	RawHitTree->Write();
	//	TruthTrackTree->Write();
	DebugFile->Write();
	DebugFile->Close();

	if (m_jsonOut.is_open())
	{
		m_jsonOut << "]" << endl;
		m_jsonOut << "}" << endl;

		m_jsonOut.close();
	}

	cout << "HFMLTriggerInterface::End - output to " << _foutname << ".*" << endl;

	return Fun4AllReturnCodes::EVENT_OK;
}

int HFMLRealData::load_nodes(PHCompositeNode* topNode)
{
	//   cout << "Loading Nodes Bro" << endl;
	m_hitsets = findNode::getClass<TrkrHitSetContainer>(topNode, "TRKR_HITSET");
	if (!m_hitsets)
	{
		std::cout << PHWHERE << "ERROR: Can't find node TRKR_HITSET" << std::endl;
		return Fun4AllReturnCodes::ABORTEVENT;
	}

	m_clus = findNode::getClass<TrkrClusterContainer>(topNode, "TRKR_CLUSTER");
	if (!m_clus)
	{
		std::cout << PHWHERE << "ERROR: Can't find node TRKR_CLUSTER" << std::endl;
		return Fun4AllReturnCodes::ABORTEVENT;
	}

	actsGeom = findNode::getClass<ActsGeometry>(topNode, "ActsGeometry");
	if (!actsGeom)
	{
		std::cout << PHWHERE << "ERROR: Can't find node actsGeom" << std::endl;
		return Fun4AllReturnCodes::ABORTEVENT;
	}

	m_si_seeds = findNode::getClass<TrackSeedContainer>(topNode, "SiliconTrackSeedContainer");
	if (!m_si_seeds)
	{
		std::cout << PHWHERE << "ERROR: Can't find node TrackSeedContainer" << std::endl;
		return Fun4AllReturnCodes::ABORTEVENT;
	}


	//    cout << "Loading Nodes Bro - Pass 1" << endl;

	std::cout << "Loaded Node Tree" << std::endl;
	return Fun4AllReturnCodes::EVENT_OK;
}
