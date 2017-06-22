/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef itkTextureMovingHistogramImageFilter_h
#define itkTextureMovingHistogramImageFilter_h

#include "itkMovingHistogramImageFilter.h"
#include "itkTextureHistogram.h"

namespace itk
{
/**
 * \class TextureMovingHistogramImageFilter
 * \brief Compute first order statistics in a neighborhood for each
 * pixel.
 *
 * The output of this filter is a multi-component image where each
 * pixel is the mean, minimum, maximum, variance, standard deviation
 * (sigma), skewness, kurtosis, and entropy. These first order
 * statistics are computed based on a define neighborhood or kernel
 * which defaults to a hyper-cube.
 *
 * The boundary is handle by only considering the pixel in the image,
 * so that the boundary pixel have lets data to compute the
 * statistics.
 *
 * \ingroup ITKTextureFeatures
 */

template< class TInputImage, class TOutputImage, class TKernel >
class ITK_TEMPLATE_EXPORT TextureMovingHistogramImageFilter:
  public MovingHistogramImageFilter< TInputImage,
                                     TOutputImage,
                                     TKernel,
                                     typename Function::TextureHistogram< typename TInputImage::PixelType,
                                                                          typename TOutputImage::PixelType > >
{
public:
  /** Standard class typedefs. */
  typedef TextureMovingHistogramImageFilter Self;
  typedef MovingHistogramImageFilter< TInputImage, TOutputImage, TKernel,
    typename Function::TextureHistogram< typename TInputImage::PixelType,  typename TOutputImage::PixelType> >  Superclass;
  typedef SmartPointer< Self >       Pointer;
  typedef SmartPointer< const Self > ConstPointer;

  /** Standard New method. */
  itkNewMacro(Self);

  /** Runtime information support. */
  itkTypeMacro(TextureMovingHistogramImageFilter,
               MovingHistogramMorphologyImageFilter);

  /** Image related typedefs. */
  typedef TInputImage                                InputImageType;
  typedef TOutputImage                               OutputImageType;
  typedef typename TInputImage::RegionType           RegionType;
  typedef typename TInputImage::SizeType             SizeType;
  typedef typename TInputImage::IndexType            IndexType;
  typedef typename TInputImage::PixelType            PixelType;
  typedef typename TInputImage::OffsetType           OffsetType;
  typedef typename Superclass::OutputImageRegionType OutputImageRegionType;
  typedef typename TOutputImage::PixelType           OutputPixelType;

  /** Image related typedefs. */
  itkStaticConstMacro(ImageDimension, unsigned int,
                      TInputImage::ImageDimension);
protected:

  unsigned int GetNumberOfOutputComponents() { return 8;}

  TextureMovingHistogramImageFilter()
  {
  }

  void GenerateOutputInformation()
  {
    // this methods is overloaded so that if the output image is a
    // VectorImage then the correct number of components are set.

    Superclass::GenerateOutputInformation();
    OutputImageType* output = this->GetOutput();

    if ( !output )
      {
      return;
      }
    if ( output->GetNumberOfComponentsPerPixel() != this->GetNumberOfOutputComponents() )
      {
      output->SetNumberOfComponentsPerPixel( this->GetNumberOfOutputComponents() );
      }
  }


  ~TextureMovingHistogramImageFilter() {}
private:
  TextureMovingHistogramImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);                  //purposely not implemented
};                                               // end of class
} // end namespace itk

#endif
