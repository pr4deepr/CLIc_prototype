

#include "cleGreaterOrEqualConstantKernel.hpp"

namespace cle
{

void GreaterOrEqualConstantKernel::SetInput(Buffer& x)
{
    this->AddObject(x, "src1");
}

void GreaterOrEqualConstantKernel::SetOutput(Buffer& x)
{
    this->AddObject(x, "dst");
}

void GreaterOrEqualConstantKernel::SetScalar(float x)
{
    this->AddObject(x, "scalar");
}

void GreaterOrEqualConstantKernel::Execute()
{
    if(this->m_Sources.size() > 1)
    {
        this->ManageDimensions("dst");
    }
    this->BuildProgramKernel();
    this->SetArguments();
    this->EnqueueKernel();
}
} // namespace cle
