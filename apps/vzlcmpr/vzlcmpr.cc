#include "sfm/bundler_common.h"
#include "sfm/visualizer.h"
#include "mve/image_tools.h"
#include "mve/image_io.h"

#include <fstream>
#include <iostream>
#include <string>

int
main (int argc, char** argv)
{
	if( argc == 6 )
	{
		std::string filename = argv[1];
		int id1 = atoi(argv[2]);
		int id2 = atoi(argv[3]);
		std::string path1 = argv[4];
		std::string path2 = argv[5];


		sfm::bundler::ViewportList viewports = std::vector<sfm::bundler::Viewport>();
		sfm::bundler::PairwiseMatching matching = std::vector<sfm::bundler::TwoViewMatching>();

		sfm::Correspondences vis_matches;

		std::cout << "prepim" << std::endl;

		sfm::bundler::load_prebundle_from_file (filename, &viewports, &matching);
		
		std::cout << "prebundler has been loaded..." << std::endl;

		sfm::bundler::Viewport viewport1 = viewports[id1];
		sfm::bundler::Viewport viewport2 = viewports[id2];

		std::cout << "Dimensions: " << viewport1.width << "x" << viewport1.height << std::endl;

		mve::ByteImage::Ptr image1 = mve::image::load_file (path1);
		mve::ByteImage::Ptr image2 = mve::image::load_file (path2);

		image1 = mve::image::rescale_half_size<uint8_t>(image1);
		image2 = mve::image::rescale_half_size<uint8_t>(image2);
		image1 = mve::image::rescale_half_size<uint8_t>(image1);
		image2 = mve::image::rescale_half_size<uint8_t>(image2);
		
		std::cout << "images have been loaded..." << std::endl;


		for(unsigned int i = 0; i < matching.size(); i++ )
		{
			sfm::bundler::TwoViewMatching tvm = matching[i];
			if( ((tvm.view_1_id == id1) && (tvm.view_2_id == id2))) //|| ((tvm.view_1_id == id2) && (tvm.view_2_id == id1)) )
			{
				for (unsigned int k= 0; k < tvm.matches.size(); k++) {
		    		sfm::Correspondence match;
		  		match.p1[0] = viewport1.features.positions[tvm.matches[k].first][0];
		    		match.p1[1] = viewport1.features.positions[tvm.matches[k].first][1];
		    		match.p2[0] = viewport2.features.positions[tvm.matches[k].second][0];
		    		match.p2[1] = viewport2.features.positions[tvm.matches[k].second][1];
        			vis_matches.push_back(match);
				}
				std::cout << "correct ids " << std::endl;
				break;
			}
		}


	std::cout << "Drawing " << vis_matches.size() << " matches..." << std::endl;
    	mve::ByteImage::Ptr match_image = sfm::Visualizer::draw_matches(image1, image2, vis_matches);
	std::cout << "Saving File" << std::endl;
	match_image = mve::image::rescale_half_size<uint8_t>(match_image);
	//match_image = mve::image::rescale_half_size<uint8_t>(match_image);
	std::string firstid = argv[2];
	std::string secondid = argv[3];
	std::string savepath = "/tmp/region_" + firstid + "_" + secondid + ".png";
	mve::image::save_file (match_image, savepath);
	std::cout << "Saved" << std::endl;
	}
	else
	{
		std::cout 	<< "Invalid arguments [filename][id1][id2][path1][path2]\n" 
					<< "\t filename of the prebundle.sfm (filepath)\n"
					<< "\t id1 is the id of the first image\n"
					<< "\t id2 is the id of the second image"
					<< "\t path1 filepath to the first image\n"
					<< "\t path2 filepath to the second image"
					<< std::endl;
	}
}
