
#include <algorithm>

#include "itkHausdorffDistanceImageFilter.h"
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkLabelOverlapMeasuresImageFilter.h"
#include "itkSignedMaurerDistanceMapImageFilter.h"

#include <iomanip>
#include <vector>

using namespace std;


template <unsigned int ImageDimension>
int LabelOverlapMeasures( int argc, char * argv[] )
{
	if( argc < 2 )
	{
		cout << "missing 1st filename" << std::endl;
		throw;
	}
	if( argc < 3 )
	{
		cout << "missing 2nd filename" << std::endl;
		throw;
	}
	typedef unsigned int                          PixelType;
	typedef itk::Image<PixelType, ImageDimension> ImageType;

	typedef itk::ImageFileReader<ImageType> ReaderType;
	typename ReaderType::Pointer reader1 = ReaderType::New();
	reader1->SetFileName( argv[2] );
	typename ReaderType::Pointer reader2 = ReaderType::New();
	reader2->SetFileName( argv[3] );

	typedef itk::LabelOverlapMeasuresImageFilter<ImageType> FilterType;
	typename FilterType::Pointer filter = FilterType::New();
	filter->SetSourceImage( reader1->GetOutput() );
	filter->SetTargetImage( reader2->GetOutput() );
	filter->Update();

	cout << "                                          "
		<< "************ All Labels *************" << std::endl;
	cout << std::setw( 10 ) << "   "
		<< std::setw( 17 ) << "Total"
		<< std::setw( 17 ) << "Union (jaccard)"
		<< std::setw( 17 ) << "Mean (dice)"
		<< std::setw( 17 ) << "Volume sim."
		<< std::setw( 17 ) << "False negative"
		<< std::setw( 17 ) << "False positive" << std::endl;
	cout << std::setw( 10 ) << "   ";
	cout << std::setw( 17 ) << filter->GetTotalOverlap();
	cout << std::setw( 17 ) << filter->GetUnionOverlap();
	cout << std::setw( 17 ) << filter->GetMeanOverlap();
	cout << std::setw( 17 ) << filter->GetVolumeSimilarity();
	cout << std::setw( 17 ) << filter->GetFalseNegativeError();
	cout << std::setw( 17 ) << filter->GetFalsePositiveError();
	cout << std::endl;

	cout << "                                       "
		<< "************ Individual Labels *************" << std::endl;
	cout << std::setw( 10 ) << "Label"
		<< std::setw( 17 ) << "Target"
		<< std::setw( 17 ) << "Union (jaccard)"
		<< std::setw( 17 ) << "Mean (dice)"
		<< std::setw( 17 ) << "Volume sim."
		<< std::setw( 17 ) << "False negative"
		<< std::setw( 17 ) << "False positive"
		//            << std::setw( 17 ) << "Hausdorff"
		//            << std::setw( 17 ) << "Avg. Hausdorff"
		//            << std::setw( 17 ) << "Min. dist. sum"
		<< std::endl;

	typename FilterType::MapType labelMap = filter->GetLabelSetMeasures();
	typename FilterType::MapType::const_iterator it;
	for( it = labelMap.begin(); it != labelMap.end(); ++it )
	{
		if( (*it).first == 0 )
		{
			continue;
		}

		int label = (*it).first;

		cout << std::setw( 10 ) << label;
		cout << std::setw( 17 ) << filter->GetTargetOverlap( label );
		cout << std::setw( 17 ) << filter->GetUnionOverlap( label );
		cout << std::setw( 17 ) << filter->GetMeanOverlap( label );
		cout << std::setw( 17 ) << filter->GetVolumeSimilarity( label );
		cout << std::setw( 17 ) << filter->GetFalseNegativeError( label );
		cout << std::setw( 17 ) << filter->GetFalsePositiveError( label );

		/**
		* Calculate distance-related measures which, perhaps, aren't considered
		* "label overlap measures" in a precise sense but are still used to determine
		* segmentation/registration accuracy. These measurements include
		*     1. Hausdorff distance
		*     2. Min distance sum
		*/

		//    typedef itk::BinaryThresholdImageFilter<ImageType, ImageType> ThresholderType;
		//    typename ThresholderType::Pointer source = ThresholderType::New();
		//    source->SetInput( filter->GetSourceImage() );
		//    source->SetLowerThreshold( label );
		//    source->SetUpperThreshold( label );
		//    source->SetInsideValue( static_cast<PixelType>( 1 ) );
		//    source->SetOutsideValue( static_cast<PixelType>( 0 ) );
		//    source->Update();
		//
		//    typename ThresholderType::Pointer target = ThresholderType::New();
		//    target->SetInput( filter->GetTargetImage() );
		//    target->SetLowerThreshold( label );
		//    target->SetUpperThreshold( label );
		//    target->SetInsideValue( static_cast<PixelType>( 1 ) );
		//    target->SetOutsideValue( static_cast<PixelType>( 0 ) );
		//    target->Update();
		//
		//    // Calculate Hausdorff distances
		//    typedef itk::HausdorffDistanceImageFilter<ImageType, ImageType> HausdorffType;
		//    typename HausdorffType::Pointer hausdorff = HausdorffType::New();
		//    hausdorff->SetInput1( source->GetOutput() );
		//    hausdorff->SetInput2( target->GetOutput() );
		//    hausdorff->Update();
		//
		//    cout << std::setw( 17 ) << hausdorff->GetHausdorffDistance();
		//    cout << std::setw( 17 ) << hausdorff->GetAverageHausdorffDistance();
		//
		//    // Calculate min sum distance
		//
		//    typedef itk::SignedMaurerDistanceMapImageFilter<ImageType, ImageType> DistancerType;
		//    typename DistancerType::Pointer sourceDistance = DistancerType::New();
		//    sourceDistance->SetInput( source->GetOutput() );
		//    sourceDistance->SetSquaredDistance( false );
		//    sourceDistance->SetUseImageSpacing( true );
		//    sourceDistance->SetInsideIsPositive( false );
		//    sourceDistance->Update();
		//
		//    typename DistancerType::Pointer targetDistance = DistancerType::New();
		//    targetDistance->SetInput( target->GetOutput() );
		//    targetDistance->SetSquaredDistance( false );
		//    targetDistance->SetUseImageSpacing( true );
		//    targetDistance->SetInsideIsPositive( false );
		//    targetDistance->Update();
		//
		//    float distanceToSource = 0.0;
		//    float NS = 0.0;
		//    float distanceToTarget = 0.0;
		//    float NT = 0.0;
		//
		//    itk::ImageRegionIteratorWithIndex<ImageType> ItS( sourceDistance->GetOutput(),
		//      sourceDistance->GetOutput()->GetLargestPossibleRegion() );
		//    itk::ImageRegionIteratorWithIndex<ImageType> ItT( targetDistance->GetOutput(),
		//      targetDistance->GetOutput()->GetLargestPossibleRegion() );
		//    for( ItS.GoToBegin(), ItT.GoToBegin(); !ItS.IsAtEnd(); ++ItS, ++ItT )
		//      {
		//      // on the boundary or inside the source object?
		//      if( ItS.Get() <= 0.0 )
		//        {
		//        // outside the target object?
		//        if( ItT.Get() > 0.0 )
		//          {
		//          distanceToTarget += ItT.Get();
		//          NS += 1.0;
		//          }
		//        }
		//
		//      // on the boundary or inside the target object?
		//      if( ItT.Get() <= 0.0 )
		//        {
		//        // outside the source object?
		//        if( ItS.Get() > 0.0 )
		//          {
		//          distanceToSource += ItS.Get();
		//          NT += 1.0;
		//          }
		//        }
		//      }
		//    float minDistanceSum = ( distanceToSource + distanceToTarget ) / ( NS + NT );
		//    cout << std::setw( 17 ) << minDistanceSum;

		cout << std::endl;
	}

	return EXIT_SUCCESS;
}


int main( int argc, char *argv[] )
{
	
	if( argc < 4 )
	{
		cout << "Usage: " << argv[0] << " imageDimension sourceImage "
			<< "targetImage" << std::endl;
		if( argc >= 2 &&
			( std::string( argv[1] ) == std::string("--help") || std::string( argv[1] ) == std::string("-h") ) )
		{
			return EXIT_SUCCESS;
		}
		return EXIT_FAILURE;
	}

	switch( atoi( argv[1] ) )
	{
	case 2:
		{
			LabelOverlapMeasures<2>( argc, argv );
		}
		break;
	case 3:
		{
			LabelOverlapMeasures<3>( argc, argv );
		}
		break;
	default:
		cout << "Unsupported dimension" << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}


