import argparse
import itk


def labelmap_combiner(input_filenames, output_filename, label_for_undecided_pixels):
    PixelType = itk.US  # itk.ctype('unsigned short')
    Dimension = 3
    ImageType = itk.Image[PixelType, Dimension]
    filter = itk.LabelVotingImageFilter[ImageType, ImageType].New()
    for input_filename in input_filenames:
        image = itk.imread(input_filename)
        filter.PushBackInput(image)
    filter.SetLabelForUndecidedPixels(label_for_undecided_pixels)
    filter.Update()
    itk.imwrite(filter, output_filename)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Use majority voting to combine multilabel images")
    parser.add_argument("output_file")
    parser.add_argument("label_for_undecided_pixels", type=int)
    parser.add_argument("input_files", nargs='+')
    args = parser.parse_args()
    output_filename = args.output_file
    input_filenames = args.input_files
    label_for_undecided_pixels = args.label_for_undecided_pixels
    labelmap_combiner(input_filenames, output_filename, label_for_undecided_pixels)
