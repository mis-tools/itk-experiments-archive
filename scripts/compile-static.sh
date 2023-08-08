#!/usr/bin/env bash
set -e
set -x
script_dir=$(dirname "$0")
cwd=`pwd`

outputdir=$2

old_method=true
if [[ "$old_method" == true ]]; then
    # use a hardcoded version of itk, downloaded
    # as a tar ball and compiled from source
    #itk_version="4.5.0"
    #itk_version="4.7.2"
    itk_version=4.8.2
    itk_dir_prefix="InsightToolkit"
    source ${script_dir}/dwn_itk.sh $itk_dir_prefix $itk_version $outputdir

    itk_dir="$outputdir/$itk_dir_prefix-$itk_version"
else
    # use git submodule checkout version of itk,
    # needs to have added itk as git submodule deps/ITK
    itk_dir="deps/ITK"
fi

# build dependencies
build_script=$1
source $build_script $itk_dir

# make
build_dir="$outputdir/build/static"
install_dir="../../static"
rm -rf ${build_dir} ${install_dir}
mkdir -p ${build_dir}
cd ${build_dir}
cmake ../../.. \
-DCMAKE_INSTALL_PREFIX=${install_dir} \
-DCMAKE_BUILD_TYPE=Release \
-DITK_DIR=$cwd/$itk_dir/build \
-DCMAKE_INSTALL_RPATH_USE_LINK_PATH=TRUE \
-DCMAKE_EXE_LINKER_FLAGS="-static" 
#-DCUDA_TOOLKIT_ROOT_DIR=/usr/local/cuda-6.5
n=`nproc`
make -j $n
make install
cd $cwd
