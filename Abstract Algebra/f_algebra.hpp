template<template<typename> class F>
struct Fix
  : F<Fix<F>>
{
    explicit Fix(F<Fix<F>> f)
      : F<Fix<F>>(f)
    {}
};

template<template<typename> class F>
Fix<F> Fx(F<Fix<F>> f)
{
    return Fix<F>{f};
}

template<template<typename> class F>
F<Fix<F>> unFix(Fix<F> f)
{
    return f;
}    