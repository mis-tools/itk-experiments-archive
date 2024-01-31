# python reimplementation of original: DicomSeriesReadImageWrite2.cxx
# using: https://itkpythonpackage.readthedocs.io/en/master/Quick_start_guide.html

# original DicomSeriesReadImageWrite2.cxx has since been rewritten in: https://examples.itk.org/src/io/gdcm/readdicomseriesandwrite3dimage/documentation including python code

# cmd: python3 DicomSeriesReadImageWrite2.py path_to_input_dicom_dir path_to_output_file.nii

import itk
import os
import sys
# from packaging import version


def load_dicom_folder(dirName, PixelType=itk.ctype("signed short")):
    # from: https://itk.org/ITKExamples/src/IO/GDCM/ReadDICOMSeriesAndWrite3DImage/Documentation.html
    Dimension = 3
    ImageType = itk.Image[PixelType, Dimension]

    namesGenerator = itk.GDCMSeriesFileNames.New()
    namesGenerator.SetUseSeriesDetails(True)
    namesGenerator.AddSeriesRestriction("0008|0021")
    namesGenerator.SetGlobalWarningDisplay(False)
    namesGenerator.SetDirectory(dirName)
    seriesUID = namesGenerator.GetSeriesUIDs()
    if len(seriesUID) != 1:
        msg = "Multiple series UID encountered: " + ", ".join(seriesUID)
        raise Exception(msg)
    for uid in seriesUID:
        seriesIdentifier = uid
        # print("Reading: " + seriesIdentifier)
        fileNames = namesGenerator.GetFileNames(seriesIdentifier)
        reader = itk.ImageSeriesReader[ImageType].New()
        dicomIO = itk.GDCMImageIO.New()
        reader.SetImageIO(dicomIO)
        reader.SetFileNames(fileNames)
    reader.Update()
    image = reader.GetOutput()
    return image


def load_image(input_filename, PixelType=itk.ctype("signed short")):
    # itk_version = version.parse(itk.Version.GetITKVersion())
    # if itk_version > version.parse("5.2.0"):
    if False:  # PNR-1101 always set to false to work around:
        # Exception: "TypeError: Expecting argument of type
        # itkImageUS3 or itkImageSourceIUS3.", as this fails in
        # the pipeline and automated tests"
        # not working for either dicom folders or
        # nifti images in itk 5.1.2
        image = itk.imread(input_filename)
    else:
        if os.path.isdir(input_filename):
            image = load_dicom_folder(input_filename, PixelType)
        else:
            Dimension = 3
            ImageType = itk.Image[PixelType, Dimension]
            reader = itk.ImageSeriesReader[ImageType].New()
            dicomIO = itk.NiftiImageIO.New()
            reader.SetImageIO(dicomIO)
            reader.SetFileName(input_filename)
            reader.Update()
            image = reader.GetOutput()
    return image


def dicom_converter(input_filename, output_filename):
    image = load_image(input_filename)
    itk.imwrite(image, output_filename)


if __name__ == "__main__":
    input_filename = sys.argv[1]
    output_filename = sys.argv[2]
    dicom_converter(input_filename, output_filename)
