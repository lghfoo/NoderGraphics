#pragma once
#include"../../../core/view/main_view.hpp"
#include"../../../core/controller/node_controller.hpp"
#include"../../../core/controller/application_controller.hpp"
#include"../../../applications/filer/controller/application_controller.hpp"
#include"../../../applications/mather/controller/application_controller.hpp"
#include"binaryzation_bernsen_node_controller.hpp"
#include"binaryzation_kittler_node_controller.hpp"
#include"binaryzation_otsu_node_controller.hpp"
#include"grayen_node_controller.hpp"
#include"image_histogram_node_controller.hpp"
#include"image_node_controller.hpp"
#include"ppm_fimage_node_controller.hpp"
#include"node_controlleres.hpp"
namespace Imager {
    class ApplicationController : public NoderGraphics::ApplicationController{
        using AddNodeHandler = MainView::AddNodeHandler;
    public:
        ApplicationController(){
            main_view->AddContextAction("Image", GetAddNodeHandler<ImageNodeController>());
            main_view->AddContextAction("File/PPM", GetAddNodeHandler<PPMFImageNodeController>());
            main_view->AddContextAction("Operation/Grayen", GetAddNodeHandler<GrayenNodeController>());
            main_view->AddContextAction("Operation/Binaryzation/OTSU", AddOTSUNodeHandler());
            main_view->AddContextAction("Operation/Binaryzation/Kittler", AddKittlerNodeHandler());
            main_view->AddContextAction("Operation/Binaryzation/Bernsen", GetAddNodeHandler<BernsenNodeController>());
            main_view->AddContextAction("Generate/Noise/Gaussian", GetAddNodeHandler<GaussianNoiseNodeController>());
            main_view->AddContextAction("Generate/Noise/Voronoi", GetAddNodeHandler<VoronoiNoiseNodeController>());
            main_view->AddContextAction("Histogram", GetAddNodeHandler<ImageHistogramNodeController>());
            main_view->AddContextAction("Mather/Histogram", GetAddNodeHandler<Mather::HistogramValueNodeController>());
            main_view->AddContextAction("Filer/File", GetAddNodeHandler<Filer::SelectFileNodeController>());
        }

        static AddNodeHandler AddOTSUNodeHandler(){
            static QString name = "OTSU Node";
            static auto Ret = GetAddNodeHandler<OTSUNodeController>(&name);
            return Ret;
        }

        static AddNodeHandler AddKittlerNodeHandler(){
            static QString name = "Kittler Node";
            static auto Ret = GetAddNodeHandler<KittlerNodeController>(&name);
            return Ret;
        }
    };
}
