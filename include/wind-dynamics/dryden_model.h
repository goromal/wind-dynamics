#pragma once

#include "utils/modeling.h"
#include <random>
#include <chrono>

//#include <iostream>

using namespace modeling;

namespace dryden_model {

class GustModelBase
{
private:
    std::default_random_engine random_generator_;
    std::normal_distribution<double> gust_dist_;
    LTIModelSISO model_;
    bool initialized_;

protected:
    MatrixXd alpha_;
    MatrixXd beta_;

    double V_;
    double sigma_;
    double L_;

    virtual void constructAlphaAndBeta() = 0;
//    {
//        alpha_.resize(2, 1);
//        beta_.resize(1, 1);
//        alpha_ << 0., 0.;
//        beta_ << 0.;
//    }

public:
    GustModelBase()
    {
        random_generator_ = std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());
        gust_dist_ = std::normal_distribution<double>(0.0, 1.0);
        initialized_ = false;
    }
//    GustModelBase(const double &Va0, const double &sigma, const double &L) : GustModelBase()
//    {
//        initializeParameters(Va0, sigma, L);
//    }
    void initializeParameters(const double &V0, const double &sigma, const double &L)
    {
        V_ = V0;
        sigma_ = sigma;
        L_ = L;
        constructAlphaAndBeta();
        MatrixXd x0(1, 1);
        x0 << 0.0;
        model_.setCoefficients(x0, alpha_, beta_);
        initialized_ = true;
    }
//    void setNewWindSpeed(const double &V)
//    {
//        if (initialized_)
//        {
//            V_ = V;
//            constructAlphaAndBeta();
//            model_.reLinearizeDenNum(alpha_, beta_);
//        }
//    }
    double run(const double &dt)
    {
        if (initialized_)
        {
            double u = gust_dist_(random_generator_);
//            std::cout << u << std::endl;
            return model_.run(u, dt);
        }
        else
            return 0.0;
    }
};

// OBSERVATION: output will be weakly bounded by sigma (because multiplied by 10)
class DrydenNoZeroModel : public GustModelBase
{
public:
    DrydenNoZeroModel() : GustModelBase() {}
//    DrydenXModel(const double &Va0, const double &sigma, const double &L) : GustModelBase(Va0, sigma, L) {}
protected:
    void constructAlphaAndBeta() override
    {
        alpha_.resize(2, 1);
        beta_.resize(1, 1);
        alpha_ << V_ / L_, 1.;
        beta_ << sigma_ * 10.0 * sqrt(2.0 * V_ / L_);
    }
};

class DrydenZeroModel : public GustModelBase
{
public:
    DrydenZeroModel() : GustModelBase() {}
protected:
    void constructAlphaAndBeta() override
    {
        alpha_.resize(2, 1);
        beta_.resize(2, 1);
//        alpha_ << -V_ / L_, -V_ / L_;
        alpha_ << V_ / L_, 1.;
        beta_ << V_ / L_ / sqrt(3.0), 1.;
        beta_ *= sigma_ * sqrt(3.0 * V_ / L_);
    }
};

class DrydenWind
{
public:
    DrydenWind() : initialized_(false) {}
    void initialize(const double &wx_nominal, const double &wy_nominal, const double &wz_nominal,
                    const double &wx_gust_bound, const double &wy_gust_bound, const double &wz_gust_bound)
    {
        wx_nominal_ = wx_nominal;
        wy_nominal_ = wy_nominal;
        wz_nominal_ = wz_nominal;
        wx_gust_.initializeParameters(1.0, wx_gust_bound, 100.0);
        wy_gust_.initializeParameters(1.0, wy_gust_bound, 100.0);
        wz_gust_.initializeParameters(1.0, wz_gust_bound, 100.0);
        initialized_ = true;
    }
    Vector3d getWind(const double &dt)
    {
        if (initialized_)
            return Vector3d(wx_nominal_, wy_nominal_, wz_nominal_) + Vector3d(wx_gust_.run(dt), wy_gust_.run(dt), wz_gust_.run(dt));
        else
            return Vector3d(0., 0., 0.);
    }
private:
    DrydenNoZeroModel wx_gust_;
    DrydenNoZeroModel wy_gust_;
    DrydenNoZeroModel wz_gust_;
    double wx_nominal_;
    double wy_nominal_;
    double wz_nominal_;
    bool initialized_;
};

} // end namespace dryden_model
