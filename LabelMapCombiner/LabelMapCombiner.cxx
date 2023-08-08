#include <algorithm>
#include <string>

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkLabelVotingImageFilter.h"

#include <iomanip>
#include <vector>
#include <map>

using namespace std;

int LabelVoting( int argc, char * argv[] )
{
	typedef unsigned short           PixelType;
	typedef itk::Image<PixelType, 3> ImageType;

	typedef itk::ImageFileReader<ImageType> ReaderType;

	std::vector<ImageType::Pointer> kInputImages;

	// Read in all input images.
	for (int i = 3; i < argc; ++i)
	{
		ReaderType::Pointer reader = ReaderType::New();
		reader->SetFileName( argv[i] );
		try
		{
			reader->Update();
		}
		catch (itk::ExceptionObject& kExcp)
		{
			cerr << kExcp << endl;
			return EXIT_FAILURE;
		}

		kInputImages.push_back(reader->GetOutput());
	}

	typedef itk::LabelVotingImageFilter<ImageType, ImageType> FilterType;
	FilterType::Pointer filter = FilterType::New();

	for (int i = 0; i < kInputImages.size(); ++i)
		filter->PushBackInput(kInputImages[i]);

	// Label For Undecided Pixels should match choice for "generic brain segment" e.g. 299
	PixelType label_for_undecided_pixels = std::atoi(argv[2]);
	filter->SetLabelForUndecidedPixels(label_for_undecided_pixels);

	try
	{
		filter->Update();
	}
	catch (itk::ExceptionObject& kExcp)
	{
		cerr << kExcp << std::endl;
		return EXIT_FAILURE;
	}

	typedef itk::ImageFileWriter<ImageType> WriterType;
	WriterType::Pointer writer = WriterType::New();

	writer->SetFileName(argv[1]);
	writer->SetInput(filter->GetOutput());
	try
	{
		writer->Update();
	}
	catch (itk::ExceptionObject& kExcp)
	{
		cerr << kExcp << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}


int main( int argc, char *argv[] )
{

	if( argc < 5 )
	{
		cout << "Usage: " << argv[0] << " <outputImage>"
		 << " <Label For Undecided Pixels(unsigned short)>"
			<< " <inputImage0>" << " ..." << std::endl;
		if( argc >= 2 &&
			( std::string( argv[1] ) == std::string("--help") || std::string( argv[1] ) == std::string("-h") ) )
		{
			return EXIT_SUCCESS;
		}
		return EXIT_FAILURE;
	}

	return LabelVoting( argc, argv );
}
