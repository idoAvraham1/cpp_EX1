#include <stdexcept>
#include "DetectCycle.hpp"

 namespace ariel {
     std::string DetectCycle::Execute(const Graph &g) {

         switch(g.getEdgeNegativity()) {

             case EdgeNegativity::NONE:
                 return detectCycleNoNegativeEdges(g);

             case EdgeNegativity::NEGATIVE:
                 return detectCycleWithNegativeEdges(g);

             default:
                 throw std::runtime_error("something went wrong");
         }
     }
     std::string DetectCycle::detectCycleWithNegativeEdges(const Graph &g) {
        return "0";
     }

     std::string DetectCycle::detectCycleNoNegativeEdges(const Graph &g) {
         return "0";
     }

 }