# from: https://itkpythonpackage.readthedocs.io/en/master/Quick_start_guide.html

import itk
import sys

# https://itk.org/pipermail/insight-users/2017-May/054606.html
# recreate mapping in: https://github.com/InsightSoftwareConsortium/ITK/blob/master/Modules/Core/Common/include/itkSpatialOrientation.h

ITK_COORDINATE_UNKNOWN = 0
ITK_COORDINATE_Right = 2
ITK_COORDINATE_Left = 3
ITK_COORDINATE_Posterior = 4
ITK_COORDINATE_Anterior = 5
ITK_COORDINATE_Inferior = 8
ITK_COORDINATE_Superior = 9

ITK_COORDINATE_PrimaryMinor = 0
ITK_COORDINATE_SecondaryMinor = 8
ITK_COORDINATE_TertiaryMinor = 16

ITK_COORDINATE_ORIENTATION_RIP = (ITK_COORDINATE_Right << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Inferior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Posterior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_LIP = (ITK_COORDINATE_Left << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Inferior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Posterior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_RSP = (ITK_COORDINATE_Right << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Superior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Posterior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_LSP = (ITK_COORDINATE_Left << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Superior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Posterior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_RIA = (ITK_COORDINATE_Right << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Inferior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Anterior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_LIA = (ITK_COORDINATE_Left << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Inferior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Anterior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_RSA = (ITK_COORDINATE_Right << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Superior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Anterior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_LSA = (ITK_COORDINATE_Left << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Superior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Anterior << ITK_COORDINATE_TertiaryMinor)

ITK_COORDINATE_ORIENTATION_IRP = (ITK_COORDINATE_Inferior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Right << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Posterior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_ILP = (ITK_COORDINATE_Inferior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Left << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Posterior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_SRP = (ITK_COORDINATE_Superior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Right << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Posterior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_SLP = (ITK_COORDINATE_Superior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Left << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Posterior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_IRA = (ITK_COORDINATE_Inferior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Right << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Anterior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_ILA = (ITK_COORDINATE_Inferior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Left << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Anterior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_SRA = (ITK_COORDINATE_Superior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Right << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Anterior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_SLA = (ITK_COORDINATE_Superior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Left << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Anterior << ITK_COORDINATE_TertiaryMinor)

ITK_COORDINATE_ORIENTATION_RPI = (ITK_COORDINATE_Right << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Posterior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Inferior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_LPI = (ITK_COORDINATE_Left << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Posterior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Inferior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_RAI = (ITK_COORDINATE_Right << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Anterior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Inferior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_LAI = (ITK_COORDINATE_Left << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Anterior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Inferior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_RPS = (ITK_COORDINATE_Right << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Posterior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Superior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_LPS = (ITK_COORDINATE_Left << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Posterior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Superior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_RAS = (ITK_COORDINATE_Right << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Anterior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Superior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_LAS = (ITK_COORDINATE_Left << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Anterior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Superior << ITK_COORDINATE_TertiaryMinor)

ITK_COORDINATE_ORIENTATION_PRI = (ITK_COORDINATE_Posterior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Right << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Inferior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_PLI = (ITK_COORDINATE_Posterior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Left << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Inferior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_ARI = (ITK_COORDINATE_Anterior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Right << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Inferior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_ALI = (ITK_COORDINATE_Anterior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Left << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Inferior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_PRS = (ITK_COORDINATE_Posterior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Right << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Superior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_PLS = (ITK_COORDINATE_Posterior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Left << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Superior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_ARS = (ITK_COORDINATE_Anterior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Right << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Superior << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_ALS = (ITK_COORDINATE_Anterior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Left << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Superior << ITK_COORDINATE_TertiaryMinor)

ITK_COORDINATE_ORIENTATION_IPR = (ITK_COORDINATE_Inferior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Posterior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Right << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_SPR = (ITK_COORDINATE_Superior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Posterior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Right << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_IAR = (ITK_COORDINATE_Inferior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Anterior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Right << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_SAR = (ITK_COORDINATE_Superior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Anterior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Right << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_IPL = (ITK_COORDINATE_Inferior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Posterior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Left << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_SPL = (ITK_COORDINATE_Superior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Posterior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Left << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_IAL = (ITK_COORDINATE_Inferior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Anterior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Left << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_SAL = (ITK_COORDINATE_Superior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Anterior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Left << ITK_COORDINATE_TertiaryMinor)

ITK_COORDINATE_ORIENTATION_PIR = (ITK_COORDINATE_Posterior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Inferior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Right << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_PSR = (ITK_COORDINATE_Posterior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Superior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Right << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_AIR = (ITK_COORDINATE_Anterior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Inferior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Right << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_ASR = (ITK_COORDINATE_Anterior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Superior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Right << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_PIL = (ITK_COORDINATE_Posterior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Inferior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Left << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_PSL = (ITK_COORDINATE_Posterior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Superior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Left << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_AIL = (ITK_COORDINATE_Anterior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Inferior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Left << ITK_COORDINATE_TertiaryMinor)
ITK_COORDINATE_ORIENTATION_ASL = (ITK_COORDINATE_Anterior << ITK_COORDINATE_PrimaryMinor) + \
                                 (ITK_COORDINATE_Superior << ITK_COORDINATE_SecondaryMinor) + \
                                 (ITK_COORDINATE_Left << ITK_COORDINATE_TertiaryMinor)


def get_itk_orientation(orientation_str):
    orientationMap = {}

    orientationMap["Axial"] = ITK_COORDINATE_ORIENTATION_RAI
    orientationMap["Coronal"] = ITK_COORDINATE_ORIENTATION_RSA
    orientationMap["Sagittal"] = ITK_COORDINATE_ORIENTATION_ASL
    orientationMap["RIP"] = ITK_COORDINATE_ORIENTATION_RIP
    orientationMap["LIP"] = ITK_COORDINATE_ORIENTATION_LIP
    orientationMap["RSP"] = ITK_COORDINATE_ORIENTATION_RSP
    orientationMap["LSP"] = ITK_COORDINATE_ORIENTATION_LSP
    orientationMap["RIA"] = ITK_COORDINATE_ORIENTATION_RIA
    orientationMap["LIA"] = ITK_COORDINATE_ORIENTATION_LIA
    orientationMap["RSA"] = ITK_COORDINATE_ORIENTATION_RSA
    orientationMap["LSA"] = ITK_COORDINATE_ORIENTATION_LSA
    orientationMap["IRP"] = ITK_COORDINATE_ORIENTATION_IRP
    orientationMap["ILP"] = ITK_COORDINATE_ORIENTATION_ILP
    orientationMap["SRP"] = ITK_COORDINATE_ORIENTATION_SRP
    orientationMap["SLP"] = ITK_COORDINATE_ORIENTATION_SLP
    orientationMap["IRA"] = ITK_COORDINATE_ORIENTATION_IRA
    orientationMap["ILA"] = ITK_COORDINATE_ORIENTATION_ILA
    orientationMap["SRA"] = ITK_COORDINATE_ORIENTATION_SRA
    orientationMap["SLA"] = ITK_COORDINATE_ORIENTATION_SLA
    orientationMap["RPI"] = ITK_COORDINATE_ORIENTATION_RPI
    orientationMap["LPI"] = ITK_COORDINATE_ORIENTATION_LPI
    orientationMap["RAI"] = ITK_COORDINATE_ORIENTATION_RAI
    orientationMap["LAI"] = ITK_COORDINATE_ORIENTATION_LAI
    orientationMap["RPS"] = ITK_COORDINATE_ORIENTATION_RPS
    orientationMap["LPS"] = ITK_COORDINATE_ORIENTATION_LPS
    orientationMap["RAS"] = ITK_COORDINATE_ORIENTATION_RAS
    orientationMap["LAS"] = ITK_COORDINATE_ORIENTATION_LAS
    orientationMap["PRI"] = ITK_COORDINATE_ORIENTATION_PRI
    orientationMap["PLI"] = ITK_COORDINATE_ORIENTATION_PLI
    orientationMap["ARI"] = ITK_COORDINATE_ORIENTATION_ARI
    orientationMap["ALI"] = ITK_COORDINATE_ORIENTATION_ALI
    orientationMap["PRS"] = ITK_COORDINATE_ORIENTATION_PRS
    orientationMap["PLS"] = ITK_COORDINATE_ORIENTATION_PLS
    orientationMap["ARS"] = ITK_COORDINATE_ORIENTATION_ARS
    orientationMap["ALS"] = ITK_COORDINATE_ORIENTATION_ALS
    orientationMap["IPR"] = ITK_COORDINATE_ORIENTATION_IPR
    orientationMap["SPR"] = ITK_COORDINATE_ORIENTATION_SPR
    orientationMap["IAR"] = ITK_COORDINATE_ORIENTATION_IAR
    orientationMap["SAR"] = ITK_COORDINATE_ORIENTATION_SAR
    orientationMap["IPL"] = ITK_COORDINATE_ORIENTATION_IPL
    orientationMap["SPL"] = ITK_COORDINATE_ORIENTATION_SPL
    orientationMap["IAL"] = ITK_COORDINATE_ORIENTATION_IAL
    orientationMap["SAL"] = ITK_COORDINATE_ORIENTATION_SAL
    orientationMap["PIR"] = ITK_COORDINATE_ORIENTATION_PIR
    orientationMap["PSR"] = ITK_COORDINATE_ORIENTATION_PSR
    orientationMap["AIR"] = ITK_COORDINATE_ORIENTATION_AIR
    orientationMap["ASR"] = ITK_COORDINATE_ORIENTATION_ASR
    orientationMap["PIL"] = ITK_COORDINATE_ORIENTATION_PIL
    orientationMap["PSL"] = ITK_COORDINATE_ORIENTATION_PSL
    orientationMap["AIL"] = ITK_COORDINATE_ORIENTATION_AIL
    orientationMap["ASL"] = ITK_COORDINATE_ORIENTATION_ASL
    return orientationMap[orientation_str]


def orient_scalar_volume(input_filename, output_filename, orientation, print_origin=False):
    image = itk.imread(input_filename)
    (_, (PixelType, Dimension)) = itk.template(image)
    # print(PixelType)
    # print(Dimension)

    # example from: https://itk.org/ITKExamples/src/Filtering/Colormap/ApplyAColormapToAnImage/Documentation.html

    ImageType = itk.Image[PixelType, Dimension]

    orienter = itk.OrientImageFilter[ImageType, ImageType].New()
    orienter.SetInput(image)
    orienter.SetUseImageDirection(True)
    orienter.SetDesiredCoordinateOrientation(get_itk_orientation(orientation))
    orienter.Update()

    change = itk.ChangeInformationImageFilter[ImageType].New()
    change.SetInput(orienter)
    change.SetChangeOrigin(True)

    newOrigin = AlignVolumeCenters(image, orienter)
    # print(newOrigin)
    change.SetOutputOrigin(newOrigin)
    change.Update()

    itk.imwrite(change, output_filename)

    if print_origin:
        print("Input origin is: " + stripped_str(image.GetOrigin()))
        print("Output origin is: " + stripped_str(change.GetOutput().GetOrigin()))


def AlignVolumeCenters(fixed, moving):
    size = fixed.GetLargestPossibleRegion().GetSize()
    centerFixedIndex = []
    for i in range(0, 3):
        centerFixedIndex.append(int(size[i] - 1 / 2.0))
    # print(centerFixedIndex)
    centerFixedIndex = itk.ContinuousIndex[itk.D, 3](centerFixedIndex)
    # from: https://discourse.itk.org/t/set-image-direction-from-numpy-array/844/10
    fixedCenter = fixed.TransformContinuousIndexToPhysicalPoint(centerFixedIndex)
    # print(fixedCenter)
    size = fixed.GetLargestPossibleRegion().GetSize()
    centerMovingIndex = []
    for i in range(0, 3):
        centerMovingIndex.append(int(size[i] - 1 / 2.0))
    # print(centerMovingIndex)
    centerMovingIndex = itk.ContinuousIndex[itk.D, 3](centerMovingIndex)
    movingCenter = fixed.TransformContinuousIndexToPhysicalPoint(centerMovingIndex)
    # print(movingCenter)
    moving_origin = moving.GetOutput().GetOrigin()
    originVector = []
    for i in range(0, 3):
        origin = moving_origin[i] - (movingCenter[i] - fixedCenter[i])
        originVector.append(origin)
    return originVector


def stripped_str(vec):
    return str(vec).replace("itkPointD3 (", "").replace(")", "")


if __name__ == "__main__":
    if len(sys.argv) != 4:
        msg = "Usage: python " + sys.argv[0]
        msg += " input_dicom_folder/ output.nii RAI"
        print(msg)
        exit(1)

    input_filename = sys.argv[1]
    output_filename = sys.argv[2]
    orientation = sys.argv[3]
    orient_scalar_volume(input_filename, output_filename, orientation, print_origin=True)
