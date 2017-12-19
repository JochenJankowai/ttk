/// \ingroup vtk
/// \class ttkScalarFieldCriticalPoints
/// \author Julien Tierny <julien.tierny@lip6.fr>
/// \date June 2015.
/// 
/// \brief TTK VTK-filter for the computation of critical points in PL
/// scalar fields defined on PL manifolds.
///
/// This filter computes the list of critical points of the input scalar field 
/// and classify them according to their type.
/// 
/// \param Input Input PL scalar field (vtkDataSet)
/// \param Output Output critical points (vtkDataSet)
///
/// This filter can be used as any other VTK filter (for instance, by using the 
/// sequence of calls SetInputData(), Update(), GetOutput()).
///
/// See the related ParaView example state files for usage examples within a 
/// VTK pipeline.
///
/// \b Related \b publication \n
/// "Critical points and curvature for embedded polyhedral surfaces" \n
/// Thomas Banchoff \n
/// American Mathematical Monthly, 1970.
///
/// \sa ttk::ScalarFieldCriticalPoints
/// 
#ifndef _TTK_SCALARFIELDCRITICALPOINTS_H
#define _TTK_SCALARFIELDCRITICALPOINTS_H

#ifndef _MSC_VER
// ttk baseCode includes
#include                  <ScalarFieldCriticalPoints.h>
#include                  <ttkWrapper.h>

// VTK includes -- to adapt
#include                  <vtkCellArray.h>
#include                  <vtkCharArray.h>
#include                  <vtkDataArray.h>
#include                  <vtkDataSet.h>
#include                  <vtkDataSetAlgorithm.h>
#include                  <vtkDoubleArray.h>
#include                  <vtkFiltersCoreModule.h>
#include                  <vtkFloatArray.h>
#include                  <vtkInformation.h>
#include                  <vtkIntArray.h>
#include                  <vtkObjectFactory.h>
#include                  <vtkPointData.h>
#include                  <vtkSmartPointer.h>
#include                  <vtkUnstructuredGrid.h>
#else
// VTK includes -- to adapt
#include                  <vtkCellArray.h>
#include                  <vtkCharArray.h>
#include                  <vtkDataArray.h>
#include                  <vtkDataSet.h>
#include                  <vtkDataSetAlgorithm.h>
#include                  <vtkDoubleArray.h>
#include                  <vtkFiltersCoreModule.h>
#include                  <vtkFloatArray.h>
#include                  <vtkInformation.h>
#include                  <vtkIntArray.h>
#include                  <vtkObjectFactory.h>
#include                  <vtkPointData.h>
#include                  <vtkSmartPointer.h>
#include                  <vtkUnstructuredGrid.h>

// ttk baseCode includes
#include                  <ScalarFieldCriticalPoints.h>
#include                  <ttkWrapper.h>
#endif

// in this example, this wrapper takes a data-set on the input and produces a 
// data-set on the output - to adapt.
// see the documentation of the vtkAlgorithm class to decide from which VTK 
// class your wrapper should inherit.
#ifndef TTK_PLUGIN
class VTKFILTERSCORE_EXPORT ttkScalarFieldCriticalPoints
#else
class ttkScalarFieldCriticalPoints
#endif 
  : public vtkDataSetAlgorithm, public Wrapper{

  public:
      
    static ttkScalarFieldCriticalPoints* New();
    
    vtkTypeMacro(ttkScalarFieldCriticalPoints, vtkDataSetAlgorithm);
   
    // default ttk setters
    vtkSetMacro(debugLevel_, int);

    void SetThreadNumber(int threadNumber){
      ThreadNumber = threadNumber;
      SetThreads();
    }   
    
    void SetUseAllCores(bool onOff){
      UseAllCores = onOff;
      SetThreads();
    }
    // end of default ttk setters
    
    vtkSetMacro(ScalarField, string);
    vtkGetMacro(ScalarField, string);

    vtkSetMacro(ScalarFieldId, int);
    vtkGetMacro(ScalarFieldId, int);

    vtkSetMacro(OffsetFieldId, int);
    vtkGetMacro(OffsetFieldId, int);

    vtkGetMacro(VertexBoundary, bool);
    vtkSetMacro(VertexBoundary, bool);
    
    vtkGetMacro(VertexIds, bool);
    vtkSetMacro(VertexIds, bool);
    
    vtkGetMacro(VertexScalars, bool);
    vtkSetMacro(VertexScalars, bool);
    
    vtkGetMacro(PredefinedOffset, bool);
    vtkSetMacro(PredefinedOffset, bool);
    
    vtkGetMacro(OffsetField, string);
    vtkSetMacro(OffsetField, string);
    
    int FillOutputPortInformation(int port, vtkInformation *info){
      info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkUnstructuredGrid"); 
      return 1;
    }
    
  protected:
    
    ttkScalarFieldCriticalPoints();
    
    ~ttkScalarFieldCriticalPoints();
    
    TTK_SETUP();
    
    
  private:
   
    bool                  PredefinedOffset;
    int                   ScalarFieldId, OffsetFieldId;
    bool                  VertexIds, VertexScalars, VertexBoundary;
    string                ScalarField, OffsetField;
    vector<vector<pair<int, int> > > vertexLinkEdgeList_;
    vector<pair<int, char> > criticalPoints_;
    vector<int>           sosOffsets_;
    
   
};

#endif // _TTK_SCALARFIELDCRITICALPOINTS_H
