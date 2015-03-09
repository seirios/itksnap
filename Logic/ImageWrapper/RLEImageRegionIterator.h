#ifndef RLEImageRegionIterator_h
#define RLEImageRegionIterator_h

#include "RLEImageRegionConstIterator.h"
#include "itkImageRegionIteratorWithIndex.h"

namespace itk
{
/** \class ImageRegionIterator
* \brief A multi-dimensional iterator templated over image type that walks a
* region of pixels.
*
* The itk::ImageRegionIterator is optimized for iteration speed and is the
* first choice for iterative, pixel-wise operations on an image.
* ImageRegionIterator is the least specialized of the ITK image iterator
* classes.  ImageRegionIterator is templated over the image type, and is
* constrained to walk only within the specified region and along a line
* parallel to one of the coordinate axes, "wrapping" to the next line as it
* reaches the boundary of the image.  To walk the entire image, specify the
* region to be \c image->GetRequestedRegion().
*
* Most of the functionality is inherited from the ImageRegionConstIterator.
* The current class only adds write access to image pixels.
*/
template< typename TPixel, typename RunLengthCounterType>
class ImageRegionIterator<RLEImage<TPixel, RunLengthCounterType> >
    :public ImageRegionConstIterator<RLEImage<TPixel, RunLengthCounterType> >
{
public:
    /** Standard class typedefs. */
    typedef ImageRegionIterator                Self;
    typedef ImageRegionConstIterator< RLEImage<TPixel, RunLengthCounterType> > Superclass;

    /** Types inherited from the Superclass */
    typedef typename Superclass::IndexType             IndexType;
    typedef typename Superclass::SizeType              SizeType;
    typedef typename Superclass::OffsetType            OffsetType;
    typedef typename Superclass::RegionType            RegionType;
    typedef typename Superclass::ImageType             ImageType;
    typedef typename Superclass::InternalPixelType     InternalPixelType;
    typedef typename Superclass::PixelType             PixelType;

    /** Default constructor. Needed since we provide a cast constructor. */
    ImageRegionIterator() :ImageRegionConstIterator< ImageType >(){ }

    /** Constructor establishes an iterator to walk a particular image and a
    * particular region of that image. */
    ImageRegionIterator(ImageType *ptr, const RegionType & region)
        :ImageRegionConstIterator< ImageType >(ptr, region) { }

    /** Constructor that can be used to cast from an ImageIterator to an
    * ImageRegionIterator. Many routines return an ImageIterator but for a
    * particular task, you may want an ImageRegionIterator.  Rather than
    * provide overloaded APIs that return different types of Iterators, itk
    * returns ImageIterators and uses constructors to cast from an
    * ImageIterator to a ImageRegionIterator. */
    ImageRegionIterator(const ImageIterator< ImageType > & it)
    {
        this->ImageConstIterator< ImageType >::operator=(it);
    }

protected:
    /** the construction from a const iterator is declared protected
    in order to enforce const correctness. */
    ImageRegionIterator(const ImageRegionConstIterator< ImageType > & it)
    {
        this->ImageConstIterator< ImageType >::operator=(it);
    }
    Self & operator=(const ImageRegionConstIterator< ImageType > & it)
    {
        this->ImageConstIterator< ImageType >::operator=(it);
    }
};

template< typename TPixel, typename RunLengthCounterType>
class ImageRegionIteratorWithIndex<RLEImage<TPixel, RunLengthCounterType> >
    :public ImageRegionIterator < RLEImage<TPixel, RunLengthCounterType> >
{
    //just inherit constructors
public:
    /** Default constructor. Needed since we provide a cast constructor. */
    ImageRegionIteratorWithIndex() :ImageRegionIterator< ImageType >(){ }

    /** Constructor establishes an iterator to walk a particular image and a
    * particular region of that image. */
    ImageRegionIteratorWithIndex(const ImageType *ptr, const RegionType & region) :
        ImageRegionIterator< ImageType >(ptr, region) { }

    /** Constructor that can be used to cast from an ImageIterator to an
    * ImageRegionIteratorWithIndex. Many routines return an ImageIterator, but for a
    * particular task, you may want an ImageRegionConstIterator.  Rather than
    * provide overloaded APIs that return different types of Iterators, itk
    * returns ImageIterators and uses constructors to cast from an
    * ImageIterator to a ImageRegionConstIterator. */
    ImageRegionIteratorWithIndex(const ImageIterator< ImageType > & it)
    {
        this->ImageRegionConstIterator< ImageType >::operator=(it);
        //this->ImageRegionConstIterator< ImageType >::operator=(static_cast<const ImageConstIterator<ImageType> >(it));
    }

    /** Constructor that can be used to cast from an ImageConstIterator to an
    * ImageRegionIteratorWithIndex. Many routines return an ImageIterator, but for a
    * particular task, you may want an ImageRegionConstIterator.  Rather than
    * provide overloaded APIs that return different types of Iterators, itk
    * returns ImageIterators and uses constructors to cast from an
    * ImageIterator to a ImageRegionIteratorWithIndex. */
    ImageRegionIteratorWithIndex(const ImageConstIterator< ImageType > & it)
    {
        this->ImageRegionConstIterator< ImageType >::operator=(it);
    }

}; //no additional implementation required
} // end namespace itk

#endif //RLEImageRegionIterator_h
