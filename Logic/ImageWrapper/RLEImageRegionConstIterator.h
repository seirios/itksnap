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
#ifndef RLEImageRegionConstIterator_h
#define RLEImageRegionConstIterator_h

#include "RLEImageConstIterator.h"
#include "itkImageRegionConstIterator.h"
#include "itkImageRegionConstIteratorWithIndex.h"

namespace itk
{
/** \class ImageRegionConstIterator
 * \brief A multi-dimensional iterator templated over image type that walks a
 * region of pixels.
 *
 * ImageRegionConstIterator provides read-only access to image data.  It is the
 * base class for the read/write access ImageRegionIterator.
 *
 */
template< typename TPixel, typename RunLengthCounterType>
class ImageRegionConstIterator<RLEImage<TPixel, RunLengthCounterType> >
    :public ImageConstIterator<RLEImage<TPixel, RunLengthCounterType> >
{
public:
  /** Standard class typedef. */
  typedef ImageRegionConstIterator<RLEImage<TPixel, RunLengthCounterType> >     Self;
  typedef ImageConstIterator<RLEImage<TPixel, RunLengthCounterType> > Superclass;

  /** Dimension of the image that the iterator walks.  This constant is needed so
   * functions that are templated over image iterator type (as opposed to
   * being templated over pixel type and dimension) can have compile time
   * access to the dimension of the image that the iterator walks. */
  itkStaticConstMacro(ImageIteratorDimension, unsigned int, 3);

  /**
   * Index typedef support. While these were already typdef'ed in the superclass,
   * they need to be redone here for this subclass to compile properly with gcc.
   */
  /** Types inherited from the Superclass */
  typedef typename Superclass::IndexType             IndexType;
  typedef typename Superclass::SizeType              SizeType;
  typedef typename Superclass::OffsetType            OffsetType;
  typedef typename Superclass::RegionType            RegionType;
  typedef typename Superclass::ImageType             ImageType;
  typedef typename Superclass::InternalPixelType     InternalPixelType;
  typedef typename Superclass::PixelType             PixelType;

  /** Run-time type information (and related methods). */
  itkTypeMacro(ImageRegionConstIterator, ImageConstIterator);

  /** Default constructor. Needed since we provide a cast constructor. */
  ImageRegionConstIterator() :ImageConstIterator< ImageType >(){ }

  /** Constructor establishes an iterator to walk a particular image and a
   * particular region of that image. */
  ImageRegionConstIterator(const ImageType *ptr, const RegionType & region):
    ImageConstIterator< ImageType >(ptr, region) { }

  /** Constructor that can be used to cast from an ImageIterator to an
   * ImageRegionConstIterator. Many routines return an ImageIterator, but for a
   * particular task, you may want an ImageRegionConstIterator.  Rather than
   * provide overloaded APIs that return different types of Iterators, itk
   * returns ImageIterators and uses constructors to cast from an
   * ImageIterator to a ImageRegionConstIterator. */
  ImageRegionConstIterator(const ImageIterator< ImageType > & it)
  {
    this->ImageConstIterator< ImageType >::operator=(it);
    //this->ImageConstIterator< ImageType >::operator=(static_cast<const ImageConstIterator<ImageType> >(it));
  }

  /** Constructor that can be used to cast from an ImageConstIterator to an
   * ImageRegionConstIterator. Many routines return an ImageIterator, but for a
   * particular task, you may want an ImageRegionConstIterator.  Rather than
   * provide overloaded APIs that return different types of Iterators, itk
   * returns ImageIterators and uses constructors to cast from an
   * ImageIterator to a ImageRegionConstIterator. */
  ImageRegionConstIterator(const ImageConstIterator< ImageType > & it)
  {
    this->ImageConstIterator< ImageType >::operator=(it);
  }

  /** Increment (prefix) the fastest moving dimension of the iterator's index.
   * This operator will constrain the iterator within the region (i.e. the
   * iterator will automatically wrap from the end of the row of the region
   * to the beginning of the next row of the region) up until the iterator
   * tries to moves past the last pixel of the region.  Here, the iterator
   * will be set to be one pixel past the end of the region.
   * \sa operator++(int) */
  Self &
  operator++()
  {
    m_Index[0]++;
    if (segmentRemainder > 0)
    {
        segmentRemainder--;
        return *this;
    }
      
    realIndex++;
    segmentRemainder = rlLine[realIndex].first;
      
    if (realIndex < m_LineEnd)
    return *this;

    this->Increment();
    return *this;
  }

  /** Decrement (prefix) the fastest moving dimension of the iterator's index.
   * This operator will constrain the iterator within the region (i.e. the
   * iterator will automatically wrap from the beginning of the row of the region
   * to the end of the next row of the region) up until the iterator
   * tries to moves past the first pixel of the region.  Here, the iterator
   * will be set to be one pixel past the beginning of the region.
   * \sa operator--(int) */
  Self & operator--()
  {
      m_Index[0]--;
      segmentRemainder++;
      if (segmentRemainder <= rlLine[realIndex].first)
          return *this;

      realIndex--;
      segmentRemainder = 0;

      if (realIndex >= m_LineBegin)
          return *this;

      this->Decrement();
      return *this;
  }

private:
  void Increment() // advance in a direction other than the fastest moving
  {
      // We have reached the end of the line (row), need to wrap around.
      m_Index[0] = m_BeginIndex[0];
      if (++m_Index[1] == m_BeginIndex[1] + m_Region.GetSize(1))
      {
          m_Index[1] = m_BeginIndex[1];
          m_Index[2]++;
      }
      SetIndex(m_Index);
  }

  void Decrement() // go back in a direction other than the fastest moving
  {
      // We have reached the beginning of the line (row), need to wrap around.
      m_Index[0] = m_EndIndex[0];
      if (--m_Index[1] < m_BeginIndex[1])
      {
          m_Index[1] = m_EndIndex[1];
          m_Index[2]--;
      }
      SetIndex(m_Index);
  }
};

template< typename TPixel, typename RunLengthCounterType>
class ImageRegionConstIteratorWithIndex<RLEImage<TPixel, RunLengthCounterType> >
    :public ImageRegionConstIterator < RLEImage<TPixel, RunLengthCounterType> >
{
    //just inherit constructors
public:
    /** Default constructor. Needed since we provide a cast constructor. */
    ImageRegionConstIteratorWithIndex() :ImageRegionConstIterator< ImageType >(){ }

    /** Constructor establishes an iterator to walk a particular image and a
    * particular region of that image. */
    ImageRegionConstIteratorWithIndex(const ImageType *ptr, const RegionType & region) :
        ImageRegionConstIterator< ImageType >(ptr, region) { }

    /** Constructor that can be used to cast from an ImageIterator to an
    * ImageRegionConstIterator. Many routines return an ImageIterator, but for a
    * particular task, you may want an ImageRegionConstIterator.  Rather than
    * provide overloaded APIs that return different types of Iterators, itk
    * returns ImageIterators and uses constructors to cast from an
    * ImageIterator to a ImageRegionConstIterator. */
    ImageRegionConstIteratorWithIndex(const ImageIterator< ImageType > & it)
    {
        this->ImageRegionConstIterator< ImageType >::operator=(it);
    }

}; //no additional implementation required

} // end namespace itk

#endif //RLEImageRegionConstIterator_h
