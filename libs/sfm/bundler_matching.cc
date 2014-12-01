#include <iostream>
#include <fstream>
#include <cstring>
#include <cerrno>

#include "util/exception.h"
#include "util/timer.h"
#include "sfm/sift.h"
#include "sfm/ransac.h"
#include "sfm/bundler_matching.h"



SFM_NAMESPACE_BEGIN
SFM_BUNDLER_NAMESPACE_BEGIN

void
Matching::compute (ViewportList const& viewports,
    PairwiseMatching* pairwise_matching)
{
    std::size_t num_pairs = viewports.size() * (viewports.size() - 1) / 2;
    std::size_t num_done = 0;

    if (this->progress != NULL)
    {
        this->progress->num_total = num_pairs;
        this->progress->num_done = 0;
    }

#pragma omp parallel for schedule(dynamic)
    for (std::size_t i = 0; i < num_pairs; ++i)
    {
#pragma omp critical
        {
            num_done += 1;
            if (this->progress != NULL)
                this->progress->num_done += 1;

            float percent = (num_done * 1000 / num_pairs) / 10.0f;
            std::cout << "\rMatching pair " << num_done << " of "
                << num_pairs << " (" << percent << "%)..." << std::endl;
        }
  




        std::size_t view_1_id = (std::size_t)(0.5 + std::sqrt(0.25 + 2.0 * i));
        std::size_t view_2_id = i - view_1_id * (view_1_id - 1) / 2;
//XXX const& vor view_x
        FeatureSet view_1 = viewports[view_1_id].features;
        FeatureSet view_2 = viewports[view_2_id].features;

//TODO Hier eingreifen



FeatureSet view_1_backup = view_1;
FeatureSet view_2_backup = view_2;



stringstream ss;
ss << view_1_id;
string str = ss.str();

if (str.size() < 2)
str = "0"+str;



	ifstream myfile;
	std::string filename = "/gcc/home/pschardt/achteckturm-test/views/view_00"+str+".rgn";

	char *file = (char*)filename.c_str();
	myfile.open (file, ios::in);
	if (myfile.is_open()) {
	char buf[50];
	myfile.getline(buf, 50);
	int id = atoi (buf);
	Quadrangle q1 = Quadrangle(id);
	for (int i=0; i<4; i++) {
	if (!myfile.eof())
  	{
    	    myfile.getline(buf, 50);
	    float x = atof (buf);
	    myfile.getline(buf, 50);
	    float y = atof (buf);
	    if (!(q1.isComplete())) {
	    q1.addPoint(x,y);
		if (q1.isComplete()) {
			view_1_backup.setQuad(1, q1);
		}
	    }
	}}


	myfile.getline(buf, 50);
	id = atoi (buf);
	Quadrangle q2 = Quadrangle(id);
	for (int i=0; i<4; i++) {
	if (!myfile.eof())
  	{
    	    myfile.getline(buf, 50);
	    float x = atof (buf);
	    myfile.getline(buf, 50);
	    float y = atof (buf);
	    if (!(q2.isComplete())) {
	    q2.addPoint(x,y);
		if (q2.isComplete()) {
			view_1_backup.setQuad(2, q2);
		}
	    }
	}}
	}


stringstream ss2;
ss2 << view_2_id;
str = ss2.str();

if (str.size() < 2)
str = "0"+str;

myfile.close();

	filename = "/gcc/home/pschardt/achteckturm-test/views/view_00"+str+".rgn";



	char *file2 = (char*)filename.c_str();
	myfile.open (file2, ios::in);
	if (myfile.is_open()) {

	char buf[50];
	myfile.getline(buf, 50);
	int id = atoi (buf);

	Quadrangle q1 = Quadrangle(id);
	for (int i=0; i<4; i++) {
	if (!myfile.eof())
  	{
    	    myfile.getline(buf, 50);
	    float x = atof (buf);
	    myfile.getline(buf, 50);
	    float y = atof (buf);
	    if (!(q1.isComplete())) {
	    q1.addPoint(x,y);
		if (q1.isComplete()) {
			view_2_backup.setQuad(1, q1);
		}
	    }
	}}


	myfile.getline(buf, 50);
	id = atoi (buf);
	Quadrangle q2 = Quadrangle(id);
	for (int i=0; i<4; i++) {
	if (!myfile.eof())
  	{
    	    myfile.getline(buf, 50);
	    float x = atof (buf);
	    myfile.getline(buf, 50);
	    float y = atof (buf);
	    if (!(q2.isComplete())) {
	    q2.addPoint(x,y);
		if (q2.isComplete()) {
			view_2_backup.setQuad(2, q2);
		}
	    }
	}}
	}

//XXX

//std::cout << "VIEW 1 " << view_1_backup.getQuad(1).getID() << "VIEW 2 " << view_2_backup.getQuad(1).getID() << std::endl;

if (view_1_backup.getQuad(1).getID()==view_2_backup.getQuad(1).getID()) {
//std::cout << "IN IF " << viewports[view_1_id].width << ", " << viewports[view_1_id].height << "Qkoord" << view_1_backup.q1.xCoords[1] << std::endl;
for (std::size_t i = 0; i < view_1.positions.size(); ++i) {
   //std::cout << "IF Position: " << view_1_backup.positions[i][0] << " " << view_1_backup.positions[i][1] << std::endl;
   if ((!view_1_backup.q1.isInside(view_1_backup.positions[i][0], view_1_backup.positions[i][1],viewports[view_1_id].width, viewports[view_1_id].height))
&&(!view_1_backup.q2.isInside(view_1_backup.positions[i][0], view_1_backup.positions[i][1], viewports[view_1_id].width, viewports[view_1_id].height)))
{  //std::cout << view_1_backup.positions[i][0] << ", " << view_1_backup.positions[i][1] << "wird geloescht" << std::endl;
   view_1_backup.positions.erase(view_1_backup.positions.begin()+i);
}   if ((!view_2_backup.q1.isInside(view_2_backup.positions[i][0], view_2_backup.positions[i][1], viewports[view_2_id].width, viewports[view_2_id].height))
&&(!view_2_backup.q2.isInside(view_2_backup.positions[i][0], view_2_backup.positions[i][1], viewports[view_2_id].width, viewports[view_2_id].height)))
{   //std::cout << "FEATURE AUS 2 GELOESCHT" << std::endl;
    view_2_backup.positions.erase(view_2_backup.positions.begin()+i);}
}}

/*std::cout << "DAVOR" << std::endl;

view_1_backup.compute_sift(viewports[view_1_id].image);
view_1_backup.compute_surf(viewports[view_1_id].image);
view_2_backup.compute_sift(viewports[view_2_id].image);
view_2_backup.compute_surf(viewports[view_2_id].image);

std::cout << "DAHINTEr" << std::endl;*/

/*if (view_1_backup.q2.getID()==view_2_backup.q2.getID()) {
for (std::size_t i = 0; i < view_1_backup.positions.size(); ++i) {
   if (!view_1_backup.q2.isInside(view_1_backup.positions[i][0], view_1_backup.positions[i][1]))
   view_1_backup.positions.erase(view_1_backup.positions.begin()+i);
   if (!view_2_backup.q2.isInside(view_2_backup.positions[i][0], view_2_backup.positions[i][1]))
   view_2_backup.positions.erase(view_2_backup.positions.begin()+i);
}}*/

const_cast<const FeatureSet*> (&view_1_backup);
const_cast<const FeatureSet*> (&view_2_backup);

/*std::cout << "View 1 size " << view_1.positions.size() << std::endl;
std::cout << "View 1 Backup size " << view_1_backup.positions.size() << std::endl;
std::cout << "View 2 size " << view_2.positions.size() << std::endl;
std::cout << "View 2 Backup size " << view_2_backup.positions.size() << std::endl;*/

/*
Quadrangle qtest = Quadrangle();
qtest.addPoint(0.25,0.25);
qtest.addPoint(0.5,0.25);
qtest.addPoint(0.5,0.5);
qtest.addPoint(0.25,0.5);

std::cout << "Ist 0,0 drin: " << qtest.isInside(0,0,20,20) << std::endl;
std::cout << "Ist 5,5 drin: " << qtest.isInside(5,5,20,20) << std::endl;
std::cout << "Ist 8,8 drin: " << qtest.isInside(8,8,20,20) << std::endl;
std::cout << "Ist 10,10 drin: " << qtest.isInside(10,10,20,20) << std::endl;
std::cout << "Ist 15,5 drin: " << qtest.isInside(15,5,20,20) << std::endl;
std::cout << "Ist 5,15 drin: " << qtest.isInside(5,15,20,20) << std::endl;
std::cout << "Ist 15,15 drin: " << qtest.isInside(15,15,20,20) << std::endl;*/

//XXX

//std::cout << "view1 " << view_1.sift_descr.begin() << std::endl;
//std::cout << "copy1 " << view_1_backup.sift_descr.begin() << std::endl;

//TODO ENDE
        if (view_1_backup.positions.empty() || view_2_backup.positions.empty())
            continue;

        /* Match the views. */
        util::WallTimer timer;
        std::stringstream message;
        CorrespondenceIndices matches;
        this->two_view_matching(view_1_backup, view_2_backup, &matches, message);
        std::size_t matching_time = timer.get_elapsed();

        if (matches.empty())
        {
#pragma omp critical
            std::cout << "\rPair (" << view_1_id << ","
                << view_2_id << ") rejected, "
                << message.str() << std::endl;
            continue;
        }

        /* Successful two view matching. Add the pair. */
        TwoViewMatching matching;
        matching.view_1_id = view_1_id;
        matching.view_2_id = view_2_id;
        std::swap(matching.matches, matches);

#pragma omp critical
        {
            pairwise_matching->push_back(matching);
            std::cout << "\rPair (" << view_1_id << ","
                << view_2_id << ") matched, " << matching.matches.size()
                << " inliers, took " << matching_time << " ms." << std::endl;
        }
    }

    std::cout << "\rFound a total of " << pairwise_matching->size()
        << " matching image pairs." << std::endl;
}

void
Matching::two_view_matching (FeatureSet const& view_1,
    FeatureSet const& view_2, CorrespondenceIndices* matches,
    std::stringstream& message)
{





    /* Low-res matching if number of features is large. */
    if (this->opts.use_lowres_matching
        && view_1.positions.size() * view_2.positions.size() > 1000000)
    {
        int const num_matches = view_1.match_lowres(view_2,
            this->opts.num_lowres_features);
        if (num_matches < this->opts.min_lowres_matches)
        {
            message << "only " << num_matches
                << " of " << this->opts.min_lowres_matches
                << " low-res matches.";
            return;
        }
    }





    /* Perform two-view descriptor matching. */
    sfm::Matching::Result matching_result;
    view_1.match(view_2, &matching_result);
    int num_matches = sfm::Matching::count_consistent_matches(matching_result);

    /* Require at least 8 matches. Check threshold. */
    int const min_matches_thres = std::max(8, this->opts.min_feature_matches);
    if (num_matches < min_matches_thres)
    {
        message << "matches below threshold of "
            << min_matches_thres << ".";
        return;
    }





    /* Build correspondences from feature matching result. */
    sfm::Correspondences unfiltered_matches;
    CorrespondenceIndices unfiltered_indices;
    {
        std::vector<int> const& m12 = matching_result.matches_1_2;
        for (std::size_t i = 0; i < m12.size(); ++i)
        {
            if (m12[i] < 0)
                continue;

            sfm::Correspondence match;
            match.p1[0] = view_1.positions[i][0];
            match.p1[1] = view_1.positions[i][1];
            match.p2[0] = view_2.positions[m12[i]][0];
            match.p2[1] = view_2.positions[m12[i]][1];
            unfiltered_matches.push_back(match);
            unfiltered_indices.push_back(std::make_pair(i, m12[i]));
        }
    }

    /* Pose RANSAC. */
    sfm::RansacFundamental::Result ransac_result;
    int num_inliers = 0;
    {
        sfm::RansacFundamental ransac(this->opts.ransac_opts);
        ransac.estimate(unfiltered_matches, &ransac_result);
        num_inliers = ransac_result.inliers.size();
    }

    /* Require at least 8 inlier matches. */
    int const min_inlier_thres = std::max(8, this->opts.min_matching_inliers);
    if (num_inliers < min_inlier_thres)
    {
        message << "inliers below threshold of "
            << min_inlier_thres << ".";
        return;
    }

    /* Create Two-View matching result. */
    matches->clear();
    matches->reserve(num_inliers);
    for (int i = 0; i < num_inliers; ++i)
    {
        int const inlier_id = ransac_result.inliers[i];
        matches->push_back(unfiltered_indices[inlier_id]);
    }
}

SFM_BUNDLER_NAMESPACE_END
SFM_NAMESPACE_END
