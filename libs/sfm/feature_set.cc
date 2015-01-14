#include <iostream>
#include <algorithm>

#include "sfm/feature_set.h"

SFM_NAMESPACE_BEGIN

namespace
{
    void
    convert_descriptor (Sift::Descriptor const& descr, unsigned short* data)
    {
        for (int i = 0; i < 128; ++i)
        {
            float value = descr.data[i];
            value = math::clamp(value, 0.0f, 1.0f);
            value = math::round(value * 255.0f);
            data[i] = static_cast<unsigned char>(value);
        }
    }

    void
    convert_descriptor (Surf::Descriptor const& descr, signed short* data)
    {
        for (int i = 0; i < 64; ++i)
        {
            float value = descr.data[i];
            value = math::clamp(value, -1.0f, 1.0f);
            value = math::round(value * 127.0f);
            data[i] = static_cast<signed char>(value);
        }
    }

    void
    convert_descriptor (Sift::Descriptor const& descr, float* data)
    {
        std::copy(descr.data.begin(), descr.data.end(), data);
    }

    void
    convert_descriptor (Surf::Descriptor const& descr, float* data)
    {
        std::copy(descr.data.begin(), descr.data.end(), data);
    }

    template <typename T>
    bool
    compare_scale (T const& descr1, T const& descr2)
    {
        return descr1.scale > descr2.scale;
    }

    template <typename T>
    bool
    compare_reg (T const& descr1, T const& descr2)
    {
        return descr1.reg > descr2.reg;
    }

}  /* namespace */

void
FeatureSet::compute_features (mve::ByteImage::Ptr image)
{
    this->colors.clear();
    this->positions.clear();
    this->width = image->width();
    this->height = image->height();

    /* Make sure these are in the right order. Matching relies on it. */
    if (this->opts.feature_types & FEATURE_SIFT)
        this->compute_sift(image);
    if (this->opts.feature_types & FEATURE_SURF)
        this->compute_surf(image);
}

void
FeatureSet::compute_sift (mve::ByteImage::ConstPtr image)
{
    /* Compute features. */
    Sift::Descriptors descr;
    {
        Sift sift(this->opts.sift_opts);
        sift.set_image(image);
        sift.process();
        descr = sift.get_descriptors();
    }

 
#pragma omp critical
    for (int i = descr.size()-1; i >= 0; i--) {
	descr[i].reg = -1;
	
        if (q1.isInside(descr[i].x, descr[i].y,this->width, this->height))
	descr[i].reg = q1.getID();

	if (q2.isInside(descr[i].x, descr[i].y,this->width, this->height))
	descr[i].reg = q2.getID();
    }


    /* Sort features by scale for low-res matching. */
    //std::sort(descr.begin(), descr.end(), compare_scale<sfm::Sift::Descriptor>);
    std::sort(descr.begin(), descr.end(), compare_reg<sfm::Sift::Descriptor>);
#pragma omp critical
    for (unsigned int i = 0; i < descr.size()-1; i++) {
	if (descr[i].reg != descr[i+1].reg)
	{
		int myints[] = {i, descr[i].reg};
		std::vector<int> vec (myints, myints + sizeof(myints));
		sift_regs.push_back(vec);
	}
    }

int myints[] = {descr.size() - 1, descr[(descr.size() - 1)].reg};
std::vector<int> vec (myints, myints + sizeof(myints));
sift_regs.push_back(vec);
#pragma omp critical
for (unsigned int i = 0; i < sift_regs.size(); i++) {
int off;
int off2;
if (i == 0)
off = 0;
else
off = sift_regs[i-1][0] + 1;

//if (i == sift_regs.size() - 1)
//off2 = descr.size();
//else 
off2 = sift_regs[i][0] + 1;

//std::cout << "off " << off << "off2 " << off2 << std::endl;
std::sort(descr.begin()+off, descr.begin()+off2, compare_scale<sfm::Sift::Descriptor>);
//std::sort(descr.begin()+surf_regs[0], descr.begin()+surf_regs[1], compare_scale<sfm::Surf::Descriptor>);
//std::sort(descr.begin()+surf_regs[1], descr.end(), compare_scale<sfm::Surf::Descriptor>);
}


 //Output
/*#pragma omp critical
    for (int i = 0; i < descr.size()-1; i++) {
std::cout << i << " " << descr[i].reg << " " << descr[i].scale << std::endl;
    }

std::cout << "Offsets: " << sift_regs[0] << " " << sift_regs[1] << std::endl; */

    /* Prepare and copy to data structures. */
    std::size_t offset = this->positions.size();
    this->positions.resize(offset + descr.size());
    this->colors.resize(offset + descr.size());
    this->sift_descr.allocate(descr.size() * 128);
    this->num_sift_descriptors = descr.size();

#if DISCRETIZE_DESCRIPTORS
    unsigned short* ptr = this->sift_descr.begin();
#else
    float* ptr = this->sift_descr.begin();
#endif
    for (std::size_t i = 0; i < descr.size(); ++i, ptr += 128)
    {
        Sift::Descriptor const& d = descr[i];
        convert_descriptor(d, ptr);
        this->positions[offset + i] = math::Vec2f(d.x, d.y);
        image->linear_at(d.x, d.y, this->colors[offset + i].begin());
    }
}


void
FeatureSet::compute_surf (mve::ByteImage::ConstPtr image)
{
    /* Compute features. */
    Surf::Descriptors descr;
    {
        Surf surf(this->opts.surf_opts);
        surf.set_image(image);
        surf.process();
        descr = surf.get_descriptors();
    }


#pragma omp critical
    for (int i = descr.size()-1; i >= 0; i--) {
	descr[i].reg = -1;
	
        if (q1.isInside(descr[i].x, descr[i].y,this->width, this->height))
	descr[i].reg = q1.getID();

	if (q2.isInside(descr[i].x, descr[i].y,this->width, this->height))
	descr[i].reg = q2.getID();
    }


//std::cout << "Vorher " << s << " Nachher " << descr.size() << " " << this->width << "x" << this->height << std::endl;


    /* Sort features by scale for low-res matching. */
    //std::sort(descr.begin(), descr.end(), compare_scale<sfm::Surf::Descriptor>);
    std::sort(descr.begin(), descr.end(), compare_reg<sfm::Surf::Descriptor>);


#pragma omp critical
    for (unsigned int i = 0; i < descr.size()-1; i++) {
	if (descr[i].reg != descr[i+1].reg) {
		int myints[] = {i, descr[i].reg};
		std::vector<int> vec (myints, myints + sizeof(myints));
		surf_regs.push_back(vec);
	}
    }
int myints[] = {descr.size() - 1, descr[(descr.size() - 1)].reg};
std::vector<int> vec (myints, myints + sizeof(myints));
surf_regs.push_back(vec);

//std::cout << "surf_reg_size: " << surf_regs.size() << std::endl;


#pragma omp critical
for (unsigned int i = 0; i < surf_regs.size(); i++) {
int off;
int off2;
if (i == 0)
off = 0;
else
off = surf_regs[i-1][0] + 1;

//if (i == surf_regs.size() - 1)
//off2 = descr.size();
//else 
off2 = surf_regs[i][0] + 1;

//std::cout << "off " << off << "off2 " << off2 << std::endl;
std::sort(descr.begin()+off, descr.begin()+off2, compare_scale<sfm::Surf::Descriptor>);
//std::sort(descr.begin()+surf_regs[0], descr.begin()+surf_regs[1], compare_scale<sfm::Surf::Descriptor>);
//std::sort(descr.begin()+surf_regs[1], descr.end(), compare_scale<sfm::Surf::Descriptor>);
}

 //Output
/*#pragma omp critical
    for (int i = 0; i < descr.size(); i++) {
std::cout << i << " " << descr[i].reg << " " << descr[i].scale << std::endl;
    }*/

///std::cout << "Offsets: " << sift_regs[0][0] << " " << sift_regs[1][0] << " " << sift_regs[2][0] << std::endl;


    /* Prepare and copy to data structures. */
    std::size_t offset = this->positions.size();
    this->positions.resize(offset + descr.size());
    this->colors.resize(offset + descr.size());
    this->surf_descr.allocate(descr.size() * 64);
    this->num_surf_descriptors = descr.size();

#if DISCRETIZE_DESCRIPTORS
    signed short* ptr = this->surf_descr.begin();
#else
    float* ptr = this->surf_descr.begin();
#endif
    for (std::size_t i = 0; i < descr.size(); ++i, ptr += 64)
    {
        Surf::Descriptor const& d = descr[i];
        convert_descriptor(d, ptr);
        this->positions[offset + i] = math::Vec2f(d.x, d.y);
        image->linear_at(d.x, d.y, this->colors[offset + i].begin());
    }
}


int
FeatureSet::match_lowres (FeatureSet const& other, int num_features) const
{
    /* SIFT lowres matching. */
    if (this->num_sift_descriptors > 0)
    {
        sfm::Matching::Result sift_result;
        sfm::Matching::twoway_match(this->opts.sift_matching_opts,
            this->sift_descr.begin(),
            std::min(num_features, this->num_sift_descriptors),
            other.sift_descr.begin(),
            std::min(num_features, other.num_sift_descriptors),
            &sift_result);
        return sfm::Matching::count_consistent_matches(sift_result);
    }

    /* SURF lowres matching. */
    if (this->num_surf_descriptors > 0)
    {
        sfm::Matching::Result surf_result;
        sfm::Matching::twoway_match(this->opts.surf_matching_opts,
            this->surf_descr.begin(),
            std::min(num_features, this->num_surf_descriptors),
            other.surf_descr.begin(),
            std::min(num_features, other.num_surf_descriptors),
            &surf_result);
        return sfm::Matching::count_consistent_matches(surf_result);
    }

    return 0;
}


//QuadrangleMethods
void FeatureSet::setQuad (int i, Quadrangle q) {
if (i==1) {
this->q1 = q;
}
if (i==2) {
this->q2 = q;
}
}


Quadrangle FeatureSet::getQuad (int i) {
if (i==1)
return q1;
else
return q2;
}



void
FeatureSet::match (FeatureSet const& other, Matching::Result* result) const
{

const_cast<const FeatureSet*> (&other);
//XXX
    /* SIFT matching. */
    sfm::Matching::Result sift_result;
    if (this->num_sift_descriptors > 0)
    {
	/* Original        
	sfm::Matching::twoway_match(this->opts.sift_matching_opts,
            this->sift_descr.begin(), this->num_sift_descriptors,
            other.sift_descr.begin(), other.num_sift_descriptors,
            &sift_result);
        sfm::Matching::remove_inconsistent_matches(&sift_result);*/
	

	//sfm::Matching::Result sift3;


	std::vector<sfm::Matching::Result> siftvec;
	sfm::Matching::Result sift1;
	sfm::Matching::Result sift2;
	sfm::Matching::Result sift3;
	siftvec.push_back(sift1);
	siftvec.push_back(sift2);
	siftvec.push_back(sift3);

	for (unsigned int i = 0; i < sift_regs.size(); i++) {
		for (unsigned int k = 0; k < other.sift_regs.size(); k++) {
			if (sift_regs[i][1] == other.sift_regs[k][1]) {
			int off;
			int off2;
			int num;
			int num2;
			if (i == 0) 
				off = 0;
			else
				off = sift_regs[i-1][0] + 1;
			if (k == 0)
				off2 = 0;
			else
				off2 = other.sift_regs[k-1][0] + 1;

			if (i == 0)
				num = sift_regs[i][0] + 1;
			else
				num = sift_regs[i][0] - sift_regs[i-1][0];
			if (k == 0)
				num2 = other.sift_regs[k][0] + 1;
			else
				num2 = other.sift_regs[k][0] - other.sift_regs[k-1][0];

			sfm::Matching::twoway_match(this->opts.sift_matching_opts,
            			this->sift_descr.begin()+(this->opts.sift_matching_opts.descriptor_length * off), num,		//
            			other.sift_descr.begin()+(other.opts.sift_matching_opts.descriptor_length * off2), num2,		//
            			&siftvec[i]);
			}
		}
	}
/*
	if ((sift_regs.empty())&&(other.sift_regs.empty()))
	sfm::Matching::twoway_match(this->opts.sift_matching_opts,
            this->sift_descr.begin(), this->num_sift_descriptors,													//
            other.sift_descr.begin(), other.num_sift_descriptors,													//
            &sift_result);
	if ((sift_regs.size() > 0)&&(other.sift_regs.size() > 0))
	sfm::Matching::twoway_match(this->opts.sift_matching_opts,
            this->sift_descr.begin(), this->sift_regs[0],													//
            other.sift_descr.begin(), other.sift_regs[0],													//
            &sift_result);

	if ((sift_regs.size() > 1)&&(other.sift_regs.size() > 1))
	sfm::Matching::twoway_match(this->opts.sift_matching_opts,
            this->sift_descr.begin()+(this->opts.sift_matching_opts.descriptor_length * this->sift_regs[0]), this->sift_regs[1] - this->sift_regs[0],		//
            other.sift_descr.begin()+(other.opts.sift_matching_opts.descriptor_length * other.sift_regs[0]), other.sift_regs[1] - other.sift_regs[0],		//
            &sift2);

	if ((sift_regs.size() > 2)&&(other.sift_regs.size() > 2))
	sfm::Matching::twoway_match(this->opts.sift_matching_opts,
            this->sift_descr.begin()+(this->opts.sift_matching_opts.descriptor_length * this->sift_regs[1]), this->num_sift_descriptors - this->sift_regs[1],
            other.sift_descr.begin()+(other.opts.sift_matching_opts.descriptor_length * other.sift_regs[1]), other.num_sift_descriptors - other.sift_regs[1],
            &sift3);*/

//std::cout << "sift res12: " << sift_result.matches_1_2.size() << " sift212 " << sift2.matches_1_2.size() << " sift312 " << sift3.matches_1_2.size() << std::endl;
//std::cout << "sift res21: " << sift_result.matches_2_1.size() << " sift221 " << sift2.matches_2_1.size() << " sift321 " << sift3.matches_2_1.size() << std::endl;

//std::cout << "Siftres: " << sfm::Matching::count_consistent_matches(sift_result) << std::endl;


	//int res12 = sift_result.matches_1_2.size();
	//int res21 = sift_result.matches_2_1.size();
	if (sift_regs.size() > 0) {
	for (unsigned int i = 0; i < siftvec[0].matches_1_2.size(); i++) {
		sift_result.matches_1_2.push_back(siftvec[0].matches_1_2[i]);
	}
	for (unsigned int i = 0; i < siftvec[0].matches_2_1.size(); i++) {
		sift_result.matches_2_1.push_back(siftvec[0].matches_2_1[i]);
	}}
	if (sift_regs.size() > 1) {
	for (unsigned int i = 0; i < siftvec[1].matches_1_2.size(); i++) {
		sift_result.matches_1_2.push_back(siftvec[1].matches_1_2[i] + siftvec[0].matches_2_1.size());
	}
	for (unsigned int i = 0; i < siftvec[1].matches_2_1.size(); i++) {
		sift_result.matches_2_1.push_back(siftvec[1].matches_2_1[i] + siftvec[0].matches_1_2.size());
	}}
	if (sift_regs.size() > 2) {
	for (unsigned int i = 0; i < siftvec[2].matches_1_2.size(); i++) {
		sift_result.matches_1_2.push_back(siftvec[2].matches_1_2[i] + siftvec[0].matches_2_1.size() + siftvec[1].matches_2_1.size());
	}
	for (unsigned int i = 0; i < siftvec[2].matches_2_1.size(); i++) {
		sift_result.matches_2_1.push_back(siftvec[2].matches_2_1[i] + siftvec[0].matches_1_2.size() + siftvec[1].matches_1_2.size());
	}}

//std::cout << "Sift2: " << sfm::Matching::count_consistent_matches(sift2) << std::endl;
//std::cout << "Sift3: " << sfm::Matching::count_consistent_matches(sift3) << std::endl;
//std::cout << "Siftres: " << sfm::Matching::count_consistent_matches(sift_result) << std::endl;
//std::cout << "sift res12: " << sift_result.matches_1_2.size() << std::endl;
//std::cout << "sift res21: " << sift_result.matches_2_1.size() << std::endl;


        sfm::Matching::remove_inconsistent_matches(&sift_result);

    }

    /* SURF matching. */
    sfm::Matching::Result surf_result;
    if (this->num_surf_descriptors > 0)
    {
        /*sfm::Matching::twoway_match(this->opts.surf_matching_opts,
            this->surf_descr.begin(), this->num_surf_descriptors,
            other.surf_descr.begin(), other.num_surf_descriptors,
            &surf_result);
        sfm::Matching::remove_inconsistent_matches(&surf_result);*/

	std::vector<sfm::Matching::Result> surfvec;
	sfm::Matching::Result surf1;
	sfm::Matching::Result surf2;
	sfm::Matching::Result surf3;
	surfvec.push_back(surf1);
	surfvec.push_back(surf2);
	surfvec.push_back(surf3);


	for (unsigned int i = 0; i < surf_regs.size(); i++) {
		for (unsigned int k = 0; k < other.surf_regs.size(); k++) {
			if (surf_regs[i][1] == other.surf_regs[k][1]) {
			int off;
			int off2;
			int num;
			int num2;
			if (i == 0) 
				off = 0;
			else
				off = surf_regs[i-1][0] + 1;
			if (k == 0)
				off2 = 0;
			else
				off2 = other.surf_regs[k-1][0] + 1;

			if (i == 0)
				num = surf_regs[i][0] + 1;
			else
				num = surf_regs[i][0] - surf_regs[i-1][0];
			if (k == 0)
				num2 = other.surf_regs[k][0] + 1;
			else
				num2 = other.surf_regs[k][0] - other.surf_regs[k-1][0];

			sfm::Matching::twoway_match(this->opts.surf_matching_opts,
            			this->surf_descr.begin()+(this->opts.surf_matching_opts.descriptor_length * off), num,		//
            			other.surf_descr.begin()+(other.opts.surf_matching_opts.descriptor_length * off2), num2,		//
            			&surfvec[i]);
			}
		}
	}

	/*sfm::Matching::Result surf2;
	sfm::Matching::Result surf3;

	if ((surf_regs.empty())&&(other.surf_regs.empty()))
	sfm::Matching::twoway_match(this->opts.surf_matching_opts,
            this->surf_descr.begin(), this->num_surf_descriptors,
            other.surf_descr.begin(), other.num_surf_descriptors,
            &surf_result);
	if ((surf_regs.size() > 0)&&(other.surf_regs.size() > 0))
	sfm::Matching::twoway_match(this->opts.surf_matching_opts,
            this->surf_descr.begin(), this->surf_regs[0],
            other.surf_descr.begin(), other.surf_regs[0],
            &surf_result);

	if ((surf_regs.size() > 1) && (other.surf_regs.size() > 1))
	sfm::Matching::twoway_match(this->opts.surf_matching_opts,
            this->surf_descr.begin()+(this->opts.surf_matching_opts.descriptor_length * this->surf_regs[0]), this->surf_regs[1] - this->surf_regs[0],
            other.surf_descr.begin()+(other.opts.surf_matching_opts.descriptor_length * other.surf_regs[0]), other.surf_regs[1] - other.surf_regs[0],
            &surf2);
	if ((surf_regs.size() > 2) && (other.surf_regs.size() > 2))
	sfm::Matching::twoway_match(this->opts.surf_matching_opts,
            this->surf_descr.begin()+(this->opts.surf_matching_opts.descriptor_length * this->surf_regs[1]), this->num_surf_descriptors - this->surf_regs[1],
            other.surf_descr.begin()+(other.opts.surf_matching_opts.descriptor_length * other.surf_regs[1]), other.num_surf_descriptors - other.surf_regs[1],
            &surf3);

	int res12 = surf_result.matches_1_2.size();
	int res21 = surf_result.matches_2_1.size();*/



	if (surf_regs.size() > 0) {
	for (unsigned int i = 0; i < surfvec[0].matches_1_2.size(); i++) {
		surf_result.matches_1_2.push_back(surfvec[0].matches_1_2[i]);
	}
	for (unsigned int i = 0; i < surfvec[0].matches_2_1.size(); i++) {
		surf_result.matches_2_1.push_back(surfvec[0].matches_2_1[i]);
	}}
	if (surf_regs.size() > 1) {
	for (unsigned int i = 0; i < surfvec[1].matches_1_2.size(); i++) {
		surf_result.matches_1_2.push_back(surfvec[1].matches_1_2[i] + surfvec[0].matches_2_1.size());
	}
	for (unsigned int i = 0; i < surfvec[1].matches_2_1.size(); i++) {
		surf_result.matches_2_1.push_back(surfvec[1].matches_2_1[i] + surfvec[0].matches_1_2.size());
	}}
	if (surf_regs.size() > 2) {
	for (unsigned int i = 0; i < surfvec[2].matches_1_2.size(); i++) {
		surf_result.matches_1_2.push_back(surfvec[2].matches_1_2[i] + surfvec[0].matches_2_1.size() + surfvec[1].matches_2_1.size());
	}
	for (unsigned int i = 0; i < surfvec[2].matches_2_1.size(); i++) {
		surf_result.matches_2_1.push_back(surfvec[2].matches_2_1[i] + surfvec[0].matches_1_2.size() + surfvec[1].matches_1_2.size());
	}}

        sfm::Matching::remove_inconsistent_matches(&surf_result);
    }

/*std::cout << "siftthis12  " << this->num_sift_descriptors << " " << sift_result.matches_1_2.size() << std::endl;
std::cout << "siftother21 " << other.num_sift_descriptors << " " << sift_result.matches_2_1.size() << std::endl;
std::cout << "surfthis12  " << this->num_surf_descriptors << " " << surf_result.matches_1_2.size() << std::endl;
std::cout << "surfother21 " << other.num_surf_descriptors << " " << surf_result.matches_2_1.size() << std::endl;*/

/*this->num_sift_descriptors -=2;
other.num_sift_descriptors -=2;
this->num_surf_descriptors -=2;
other.num_sift_descriptors -=2;*/

    /* Fix offsets in the matching result. */
    int other_surf_offset = other.num_sift_descriptors;			
    if (other_surf_offset > 0)
        for (std::size_t i = 0; i < surf_result.matches_1_2.size(); ++i)
            if (surf_result.matches_1_2[i] >= 0)
                surf_result.matches_1_2[i] += other_surf_offset;

    int this_surf_offset = this->num_sift_descriptors;			
    if (this_surf_offset > 0)
        for (std::size_t i = 0; i < surf_result.matches_2_1.size(); ++i)
            if (surf_result.matches_2_1[i] >= 0)
                surf_result.matches_2_1[i] += this_surf_offset;

    /* Create a combined matching result. */
    std::size_t this_num_descriptors = this->num_sift_descriptors
        + this->num_surf_descriptors;						
    std::size_t other_num_descriptors = other.num_sift_descriptors
        + other.num_surf_descriptors;						

    result->matches_1_2.clear();
    result->matches_1_2.reserve(this_num_descriptors);			
    result->matches_1_2.insert(result->matches_1_2.end(),
        sift_result.matches_1_2.begin(), sift_result.matches_1_2.end());
    result->matches_1_2.insert(result->matches_1_2.end(),
        surf_result.matches_1_2.begin(), surf_result.matches_1_2.end());

    result->matches_2_1.clear();
    result->matches_2_1.reserve(other_num_descriptors);			
    result->matches_2_1.insert(result->matches_2_1.end(),
        sift_result.matches_2_1.begin(), sift_result.matches_2_1.end());
    result->matches_2_1.insert(result->matches_2_1.end(),
        surf_result.matches_2_1.begin(), surf_result.matches_2_1.end());
}

void
FeatureSet::clear_descriptors (void)
{
    this->num_sift_descriptors = 0;
    this->sift_descr.deallocate();
    this->num_surf_descriptors = 0;
    this->surf_descr.deallocate();
}

SFM_NAMESPACE_END
