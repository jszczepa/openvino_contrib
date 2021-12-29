// Copyright (C) 2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//
#pragma once

#include <cuda_operation_base.hpp>
#include <kernels/pad.cuh>
#include <ngraph/op/pad.hpp>

namespace CUDAPlugin {

class PadOp : public OperationBase {
public:
    using NodeOp = ngraph::op::v1::Pad;
    explicit PadOp(const CreationContext& context,
                   const ngraph::op::v1::Pad& node,
                   IndexCollection&& inputIds,
                   IndexCollection&& outputIds);
    void Execute(const InferenceRequestContext& context,
                 Inputs inputTensors,
                 Outputs outputTensors,
                 const Workbuffers& workbuffers) const override;
    WorkbufferRequest GetWorkBufferRequest() const override;
    void InitSharedImmutableWorkbuffers(const Buffers&) override;

private:
    enum WorkbufferIndex {
        kSrcShape,
        kDstShape,
    };

    enum InputIndex {
        kSrc,
        kPadsBegin,
        kPadsEnd,
        kPadValue,
    };

    enum OutputIndex {
        kDst,
    };

    kernel::ConstModePad kernel_;
    ngraph::Shape src_shape_;
    ngraph::Shape dst_shape_;
};

}  // namespace CUDAPlugin