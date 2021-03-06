#include <vector>
using namespace std;

#include "Vertex.h"
#include "Mesh.h"
#include "HalfEdge.h"

namespace DDG
{
   double Vertex::area( void ) const
   // returns the dual area associated with this vertex
   {
      double A = 0.;

      HalfEdgeCIter h = he;
      do
      {
         if (not h->onBoundary) A += h->face->area();
         h = h->flip->next;
      }
      while( h != he );

      return A / 3.;
   }

   /*
   Vector Vertex::geometric_normal( void ) const
   // returns the vertex normal
   {
      Vector N;

      HalfEdgeCIter h = he;
      do
      {
         if (not h->onBoundary) N += h->face->geometric_normal();
         h = h->flip->next;
      }
      while( h != he );

      return N.unit();
   }
   */

   vector<HalfEdge> isolated; // all isolated vertices point to isolated.begin()

   Vector Vertex::getColor() const
   {
       double feature_clamped = feature_scalar;
       if (feature_clamped < 0) feature_clamped = 0;
       if (feature_clamped > 1) feature_clamped = 1;
       const Vector basic_color = inpainting ? feature_exclusion ? Vector(0,1,1) : Vector(0,1,0) : feature_exclusion ? Vector(0,0,1) : Vector(1,1,1);
       return feature_clamped*basic_color+(1-feature_clamped)*Vector(1,0,0);
   }

   bool Vertex::isIsolated( void ) const
   // returns true if the vertex is not contained in any face or edge; false otherwise
   {
      return he == isolated.begin();
   }

   int Vertex :: valence( void ) const
   // returns the number of incident faces
   {
      int n = 0;

      HalfEdgeCIter h = he;
      do
      {
         n++;
         h = h->flip->next;
      }
      while( h != he );

      return n;
   }

   void Vertex :: toggleTag()
   {
      tag = !tag;
   }
}

