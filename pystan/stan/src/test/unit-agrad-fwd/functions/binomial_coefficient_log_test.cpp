#include <gtest/gtest.h>
#include <stan/agrad/fwd.hpp>
#include <boost/math/special_functions/digamma.hpp>
#include <stan/math/functions/binomial_coefficient_log.hpp>
#include <stan/agrad/rev.hpp>
#include <test/unit/agrad/util.hpp>

TEST(AgradFwdBinomialCoefficientLog,Fvar) {
  using stan::agrad::fvar;
  using stan::math::binomial_coefficient_log;
  using boost::math::digamma;

  fvar<double> x(2004.0,1.0);
  fvar<double> y(1002.0,2.0);

  fvar<double> a = stan::agrad::binomial_coefficient_log(x, y);
  EXPECT_FLOAT_EQ(binomial_coefficient_log(2004.0, 1002.0), a.val_);
  EXPECT_FLOAT_EQ(0.69289774, a.d_);
}

TEST(AgradFwdBinomialCoefficientLog,FvarVar_Double_1stDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::binomial_coefficient_log;
  using boost::math::digamma;

  fvar<var> x(2004.0,1.0);
  double z(1002);
  fvar<var> a = binomial_coefficient_log(x,z);

  EXPECT_FLOAT_EQ(binomial_coefficient_log(2004.0,1002.0), a.val_.val());
  EXPECT_FLOAT_EQ(0.69289774, a.d_.val());

  AVEC y = createAVEC(x.val_);
  VEC g;
  a.val_.grad(y,g);
  EXPECT_FLOAT_EQ(0.69289774, g[0]);
}
TEST(AgradFwdBinomialCoefficientLog,Double_FvarVar_1stDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::binomial_coefficient_log;
  using boost::math::digamma;

  double x(2004.0);
  fvar<var> z(1002.0,2.0);
  fvar<var> a = binomial_coefficient_log(x,z);

  EXPECT_FLOAT_EQ(binomial_coefficient_log(2004.0,1002.0), a.val_.val());
  EXPECT_NEAR(0, a.d_.val(),1e-8);

  AVEC y = createAVEC(z.val_);
  VEC g;
  a.val_.grad(y,g);
  EXPECT_NEAR(0, g[0],1e-8);
}
TEST(AgradFwdBinomialCoefficientLog,FvarVar_Double_2ndDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::binomial_coefficient_log;
  using boost::math::digamma;

  fvar<var> x(2004.0,1.0);
  double z(1002);
  fvar<var> a = binomial_coefficient_log(x,z);

  EXPECT_FLOAT_EQ(binomial_coefficient_log(2004.0,1002.0), a.val_.val());
  EXPECT_FLOAT_EQ(0.69289774, a.d_.val());

  AVEC y = createAVEC(x.val_);
  VEC g;
  a.d_.grad(y,g);
  EXPECT_FLOAT_EQ(-0.00049862865, g[0]);
}
TEST(AgradFwdBinomialCoefficientLog,Double_FvarVar_2ndDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::binomial_coefficient_log;
  using boost::math::digamma;

  double x(2004.0);
  fvar<var> z(1002.0,2.0);
  fvar<var> a = binomial_coefficient_log(x,z);

  EXPECT_FLOAT_EQ(binomial_coefficient_log(2004.0,1002.0), a.val_.val());
  EXPECT_NEAR(0, a.d_.val(),1e-8);

  AVEC y = createAVEC(z.val_);
  VEC g;
  a.d_.grad(y,g);
  EXPECT_FLOAT_EQ(-0.00399002460681026, g[0]);
}


TEST(AgradFwdBinomialCoefficientLog,FvarVar_FvarVar_1stDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::binomial_coefficient_log;
  using boost::math::digamma;

  fvar<var> x(2004.0,1.0);
  fvar<var> z(1002.0,2.0);
  fvar<var> a = binomial_coefficient_log(x,z);

  EXPECT_FLOAT_EQ(binomial_coefficient_log(2004.0,1002.0), a.val_.val());
  EXPECT_FLOAT_EQ(0.69289774, a.d_.val());

  AVEC y = createAVEC(x.val_,z.val_);
  VEC g;
  a.val_.grad(y,g);
  EXPECT_FLOAT_EQ(0.69289774, g[0]);
  EXPECT_NEAR(0, g[1],1e-8);
}
TEST(AgradFwdBinomialCoefficientLog,FvarVar_FvarVar_2ndDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::binomial_coefficient_log;
  using boost::math::digamma;

  fvar<var> x(2004.0,1.0);
  fvar<var> z(1002.0,2.0);
  fvar<var> a = binomial_coefficient_log(x,z);

  EXPECT_FLOAT_EQ(binomial_coefficient_log(2004.0,1002.0), a.val_.val());
  EXPECT_FLOAT_EQ(0.69289774, a.d_.val());

  AVEC y = createAVEC(x.val_,z.val_);
  VEC g;
  a.d_.grad(y,g);
  EXPECT_FLOAT_EQ(0.0014963837, g[0]);
  EXPECT_FLOAT_EQ(-0.0029925184551076781, g[1]);
}

TEST(AgradFwdBinomialCoefficientLog,FvarFvarDouble) {
  using stan::agrad::fvar;
  using stan::math::binomial_coefficient_log;
  using stan::agrad::binomial_coefficient_log;

  fvar<fvar<double> > x;
  x.val_.val_ = 2004.0;
  x.val_.d_ = 1.0;

  fvar<fvar<double> > y;
  y.val_.val_ = 1002.0;
  y.d_.val_ = 1.0;

  fvar<fvar<double> > a = binomial_coefficient_log(x,y);

  EXPECT_FLOAT_EQ(binomial_coefficient_log(2004.0,1002.0), a.val_.val_);
  EXPECT_FLOAT_EQ(0.69289774, a.val_.d_);
  EXPECT_NEAR(0, a.d_.val_,1e-8);
  EXPECT_FLOAT_EQ(0.0009975062, a.d_.d_);
}

TEST(AgradFwdBinomialCoefficientLog,FvarFvarVar_FvarFvarVar_1stDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::binomial_coefficient_log;
  using stan::agrad::binomial_coefficient_log;

  fvar<fvar<var> > x;
  x.val_.val_ = 2004.0;
  x.val_.d_ = 1.0;

  fvar<fvar<var> > y;
  y.val_.val_ = 1002.0;
  y.d_.val_ = 1.0;

  fvar<fvar<var> > a = binomial_coefficient_log(x,y);

  EXPECT_FLOAT_EQ(binomial_coefficient_log(2004.0,1002.0), a.val_.val_.val());
  EXPECT_FLOAT_EQ(0.69289774, a.val_.d_.val());
  EXPECT_NEAR(0, a.d_.val_.val(),1e-8);
  EXPECT_FLOAT_EQ(0.0009975062, a.d_.d_.val());

  AVEC p = createAVEC(x.val_.val_,y.val_.val_);
  VEC g;
  a.val_.val_.grad(p,g);
  EXPECT_FLOAT_EQ(0.69289774, g[0]);
  EXPECT_NEAR(0, g[1],1e-8);
}
TEST(AgradFwdBinomialCoefficientLog,FvarFvarVar_Double_1stDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::binomial_coefficient_log;
  using stan::agrad::binomial_coefficient_log;

  fvar<fvar<var> > x;
  x.val_.val_ = 2004.0;
  x.val_.d_ = 1.0;

  double y(1002.0);

  fvar<fvar<var> > a = binomial_coefficient_log(x,y);

  EXPECT_FLOAT_EQ(binomial_coefficient_log(2004.0,1002.0), a.val_.val_.val());
  EXPECT_FLOAT_EQ(0.69289774, a.val_.d_.val());
  EXPECT_NEAR(0, a.d_.val_.val(),1e-8);
  EXPECT_FLOAT_EQ(0, a.d_.d_.val());

  AVEC p = createAVEC(x.val_.val_);
  VEC g;
  a.val_.val_.grad(p,g);
  EXPECT_FLOAT_EQ(0.69289774, g[0]);
}
TEST(AgradFwdBinomialCoefficientLog,Double_FvarFvarVar_1stDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::binomial_coefficient_log;
  using stan::agrad::binomial_coefficient_log;

  double x(2004.0);

  fvar<fvar<var> > y;
  y.val_.val_ = 1002.0;
  y.d_.val_ = 1.0;

  fvar<fvar<var> > a = binomial_coefficient_log(x,y);

  EXPECT_FLOAT_EQ(binomial_coefficient_log(2004.0,1002.0), a.val_.val_.val());
  EXPECT_FLOAT_EQ(0, a.val_.d_.val());
  EXPECT_NEAR(0, a.d_.val_.val(),1e-8);
  EXPECT_FLOAT_EQ(0, a.d_.d_.val());

  AVEC p = createAVEC(y.val_.val_);
  VEC g;
  a.val_.val_.grad(p,g);
  EXPECT_NEAR(0, g[0],1e-8);
}

TEST(AgradFwdBinomialCoefficientLog,FvarFvarVar_FvarFvarVar_2ndDeriv_x) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::binomial_coefficient_log;
  using stan::agrad::binomial_coefficient_log;

  fvar<fvar<var> > x;
  x.val_.val_ = 2004.0;
  x.val_.d_ = 1.0;

  fvar<fvar<var> > y;
  y.val_.val_ = 1002.0;
  y.d_.val_ = 1.0;

  fvar<fvar<var> > a = binomial_coefficient_log(x,y);

  EXPECT_FLOAT_EQ(binomial_coefficient_log(2004.0,1002.0), a.val_.val_.val());
  EXPECT_FLOAT_EQ(0.69289774, a.val_.d_.val());
  EXPECT_NEAR(0, a.d_.val_.val(),1e-8);
  EXPECT_FLOAT_EQ(0.0009975062, a.d_.d_.val());

  AVEC p = createAVEC(x.val_.val_,y.val_.val_);
  VEC g;
  a.val_.d_.grad(p,g);
  EXPECT_FLOAT_EQ(-0.00049862865, g[0]);
  EXPECT_FLOAT_EQ(0.00099750615170258105, g[1]);
}
TEST(AgradFwdBinomialCoefficientLog,FvarFvarVar_FvarFvarVar_2ndDeriv_y) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::binomial_coefficient_log;
  using stan::agrad::binomial_coefficient_log;

  fvar<fvar<var> > x;
  x.val_.val_ = 2004.0;
  x.val_.d_ = 1.0;

  fvar<fvar<var> > y;
  y.val_.val_ = 1002.0;
  y.d_.val_ = 1.0;

  fvar<fvar<var> > a = binomial_coefficient_log(x,y);

  EXPECT_FLOAT_EQ(binomial_coefficient_log(2004.0,1002.0), a.val_.val_.val());
  EXPECT_FLOAT_EQ(0.69289774, a.val_.d_.val());
  EXPECT_NEAR(0, a.d_.val_.val(),1e-8);
  EXPECT_FLOAT_EQ(0.0009975062, a.d_.d_.val());

  AVEC p = createAVEC(x.val_.val_,y.val_.val_);
  VEC g;
  a.d_.val_.grad(p,g);
  EXPECT_FLOAT_EQ(0.0009975062, g[0]);
  EXPECT_FLOAT_EQ(-0.0019950123034051291, g[1]);
}
TEST(AgradFwdBinomialCoefficientLog,Double_FvarFvarVar_2ndDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::binomial_coefficient_log;
  using stan::agrad::binomial_coefficient_log;

  double x(2004.0);

  fvar<fvar<var> > y;
  y.val_.val_ = 1002.0;
  y.d_.val_ = 1.0;

  fvar<fvar<var> > a = binomial_coefficient_log(x,y);

  EXPECT_FLOAT_EQ(binomial_coefficient_log(2004.0,1002.0), a.val_.val_.val());
  EXPECT_FLOAT_EQ(0, a.val_.d_.val());
  EXPECT_NEAR(0, a.d_.val_.val(),1e-8);
  EXPECT_FLOAT_EQ(0, a.d_.d_.val());

  AVEC p = createAVEC(y.val_.val_);
  VEC g;
  a.d_.val_.grad(p,g);
  EXPECT_NEAR(-0.00199501230340513, g[0],1e-8);
}
TEST(AgradFwdBinomialCoefficientLog,FvarFvarVar_Double_2ndDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::binomial_coefficient_log;
  using stan::agrad::binomial_coefficient_log;

  fvar<fvar<var> > x;
  x.val_.val_ = 2004.0;
  x.val_.d_ = 1.0;

  double y(1002.0);

  fvar<fvar<var> > a = binomial_coefficient_log(x,y);

  EXPECT_FLOAT_EQ(binomial_coefficient_log(2004.0,1002.0), a.val_.val_.val());
  EXPECT_FLOAT_EQ(0.69289774, a.val_.d_.val());
  EXPECT_NEAR(0, a.d_.val_.val(),1e-8);
  EXPECT_FLOAT_EQ(0, a.d_.d_.val());

  AVEC p = createAVEC(x.val_.val_);
  VEC g;
  a.val_.d_.grad(p,g);
  EXPECT_FLOAT_EQ(-0.00049862863648177515, g[0]);
}
TEST(AgradFwdBinomialCoefficientLog,FvarFvarVar_FvarFvarVar_3rdDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::binomial_coefficient_log;
  using stan::agrad::binomial_coefficient_log;

  fvar<fvar<var> > x;
  x.val_.val_ = 2004.0;
  x.val_.d_ = 1.0;

  fvar<fvar<var> > y;
  y.val_.val_ = 1002.0;
  y.d_.val_ = 1.0;

  fvar<fvar<var> > a = binomial_coefficient_log(x,y);

  EXPECT_FLOAT_EQ(binomial_coefficient_log(2004.0,1002.0), a.val_.val_.val());
  EXPECT_FLOAT_EQ(0.69289774, a.val_.d_.val());
  EXPECT_NEAR(0, a.d_.val_.val(),1e-8);
  EXPECT_FLOAT_EQ(0.0009975062, a.d_.d_.val());

  AVEC p = createAVEC(x.val_.val_,y.val_.val_);
  VEC g;
  a.d_.d_.grad(p,g);
  EXPECT_FLOAT_EQ(-9.9501847e-07, g[0]);
  EXPECT_FLOAT_EQ(9.9501847e-07, g[1]);
}
TEST(AgradFwdBinomialCoefficientLog,Double_FvarFvarVar_3rdDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::binomial_coefficient_log;
  using stan::agrad::binomial_coefficient_log;

  double x(2004.0);

  fvar<fvar<var> > y;
  y.val_.val_ = 1002.0;
  y.d_.val_ = 1.0;
  y.val_.d_ = 1.0;

  fvar<fvar<var> > a = binomial_coefficient_log(x,y);

  EXPECT_FLOAT_EQ(binomial_coefficient_log(2004.0,1002.0), a.val_.val_.val());
  EXPECT_NEAR(0, a.val_.d_.val(),1e-8);
  EXPECT_NEAR(0, a.d_.val_.val(),1e-8);
  EXPECT_FLOAT_EQ(-0.0019950124, a.d_.d_.val());

  AVEC p = createAVEC(y.val_.val_);
  VEC g;
  a.d_.d_.grad(p,g);
  EXPECT_NEAR(0, g[0],1e-8);
}
TEST(AgradFwdBinomialCoefficientLog,FvarFvarVar_Double_3rdDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::binomial_coefficient_log;
  using stan::agrad::binomial_coefficient_log;

  fvar<fvar<var> > x;
  x.val_.val_ = 2004.0;
  x.val_.d_ = 1.0;
  x.d_.val_ = 1.0;

  double y(1002.0);

  fvar<fvar<var> > a = binomial_coefficient_log(x,y);

  EXPECT_FLOAT_EQ(binomial_coefficient_log(2004.0,1002.0), a.val_.val_.val());
  EXPECT_FLOAT_EQ(0.69289774, a.val_.d_.val());
  EXPECT_FLOAT_EQ(0.69289774181268948, a.d_.val_.val());
  EXPECT_FLOAT_EQ(-0.00049862865, a.d_.d_.val());

  AVEC p = createAVEC(x.val_.val_);
  VEC g;
  a.d_.d_.grad(p,g);
  EXPECT_FLOAT_EQ(7.4613968e-07, g[0]);
}
