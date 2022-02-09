// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     cpp_templates/function/FUNCTION.h.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

#pragma once

#include <Eigen/Dense>

#include <sym/pose3.h>

namespace sym {

/**
 * Return the 2dof residual of reprojecting the landmark into the target camera and comparing
 * against the correspondence in the target camera.
 *
 * The landmark is specified as a pixel in the source camera and an inverse range; this means the
 * landmark is fixed in the source camera and always has residual 0 there (this 0 residual is not
 * returned, only the residual in the target camera is returned).
 *
 * The norm of the residual is whitened using the Barron noise model.  Whitening each component of
 * the reprojection error separately would result in rejecting individual components as outliers.
 * Instead, we minimize the whitened norm of the full reprojection error for each point.  See the
 * docstring for `NoiseModel.whiten_norm` for more information on this, and the docstring of
 * `BarronNoiseModel` for more information on the noise model.
 *
 * Args:
 *     source_pose: The pose of the source camera
 *     source_calibration_storage: The storage vector of the source camera calibration
 *     target_pose: The pose of the target camera
 *     target_calibration_storage: The storage vector of the target camera calibration
 *     source_inverse_range: The inverse range of the landmark in the source camera
 *     source_pixel: The location of the landmark in the source camera
 *     target_pixel: The location of the correspondence in the target camera
 *     weight: The weight of the factor
 *     gnc_mu: The mu convexity parameter for the Barron noise model
 *     gnc_scale: The scale parameter for the Barron noise model
 *     epsilon: Small positive value
 *     camera_model_class: The subclass of CameraCal to use as the camera model
 *
 * Outputs:
 *     res: 2dof residual of the reprojection
 *     jacobian: (2x13) jacobian of res wrt args source_pose (6), target_pose (6),
 *               source_inverse_range (1)
 *     hessian: (13x13) Gauss-Newton hessian for args source_pose (6), target_pose (6),
 *              source_inverse_range (1)
 *     rhs: (13x1) Gauss-Newton rhs for args source_pose (6), target_pose (6), source_inverse_range
 *          (1)
 */
template <typename Scalar>
void InverseRangeLandmarkAtanReprojectionErrorFactor(
    const sym::Pose3<Scalar>& source_pose,
    const Eigen::Matrix<Scalar, 5, 1>& source_calibration_storage,
    const sym::Pose3<Scalar>& target_pose,
    const Eigen::Matrix<Scalar, 5, 1>& target_calibration_storage,
    const Scalar source_inverse_range, const Eigen::Matrix<Scalar, 2, 1>& source_pixel,
    const Eigen::Matrix<Scalar, 2, 1>& target_pixel, const Scalar weight, const Scalar gnc_mu,
    const Scalar gnc_scale, const Scalar epsilon, Eigen::Matrix<Scalar, 2, 1>* const res = nullptr,
    Eigen::Matrix<Scalar, 2, 13>* const jacobian = nullptr,
    Eigen::Matrix<Scalar, 13, 13>* const hessian = nullptr,
    Eigen::Matrix<Scalar, 13, 1>* const rhs = nullptr) {
  // Total ops: 1355

  // Input arrays
  const Eigen::Matrix<Scalar, 7, 1>& _source_pose = source_pose.Data();
  const Eigen::Matrix<Scalar, 7, 1>& _target_pose = target_pose.Data();

  // Intermediate terms (350)
  const Scalar _tmp0 = std::pow(_target_pose[1], Scalar(2));
  const Scalar _tmp1 = -2 * _tmp0;
  const Scalar _tmp2 = std::pow(_target_pose[2], Scalar(2));
  const Scalar _tmp3 = -2 * _tmp2;
  const Scalar _tmp4 = _tmp1 + _tmp3 + 1;
  const Scalar _tmp5 = std::pow(_source_pose[2], Scalar(2));
  const Scalar _tmp6 = -2 * _tmp5;
  const Scalar _tmp7 = std::pow(_source_pose[1], Scalar(2));
  const Scalar _tmp8 = 1 - 2 * _tmp7;
  const Scalar _tmp9 = -source_calibration_storage(2, 0) + source_pixel(0, 0);
  const Scalar _tmp10 = _tmp9 / source_calibration_storage(0, 0);
  const Scalar _tmp11 = _tmp10 * (_tmp6 + _tmp8);
  const Scalar _tmp12 = -source_calibration_storage(3, 0) + source_pixel(1, 0);
  const Scalar _tmp13 =
      std::pow(_tmp12, Scalar(2)) / std::pow(source_calibration_storage(1, 0), Scalar(2));
  const Scalar _tmp14 = Scalar(0.5) * source_calibration_storage(4, 0);
  const Scalar _tmp15 = std::tan(_tmp14);
  const Scalar _tmp16 =
      std::pow(_tmp9, Scalar(2)) / std::pow(source_calibration_storage(0, 0), Scalar(2));
  const Scalar _tmp17 = _tmp13 + _tmp16 + epsilon;
  const Scalar _tmp18 = std::sqrt(_tmp17);
  const Scalar _tmp19 = _tmp18 * source_calibration_storage(4, 0);
  const Scalar _tmp20 = std::tan(_tmp19);
  const Scalar _tmp21 = (Scalar(1) / Scalar(4)) * std::pow(_tmp20, Scalar(2)) / _tmp17;
  const Scalar _tmp22 = _tmp21 / std::pow(_tmp15, Scalar(2));
  const Scalar _tmp23 =
      std::pow(Scalar(_tmp13 * _tmp22 + _tmp16 * _tmp22 + 1), Scalar(Scalar(-1) / Scalar(2)));
  const Scalar _tmp24 = (Scalar(1) / Scalar(2)) * _tmp20 / _tmp18;
  const Scalar _tmp25 = _tmp23 * _tmp24 / _tmp15;
  const Scalar _tmp26 = 2 * _source_pose[2];
  const Scalar _tmp27 = _source_pose[0] * _tmp26;
  const Scalar _tmp28 = 2 * _source_pose[3];
  const Scalar _tmp29 = _source_pose[1] * _tmp28;
  const Scalar _tmp30 = _tmp27 + _tmp29;
  const Scalar _tmp31 = 2 * _source_pose[0] * _source_pose[1];
  const Scalar _tmp32 = _source_pose[2] * _tmp28;
  const Scalar _tmp33 = -_tmp32;
  const Scalar _tmp34 = _tmp31 + _tmp33;
  const Scalar _tmp35 = _tmp12 / source_calibration_storage(1, 0);
  const Scalar _tmp36 = _tmp25 * _tmp35;
  const Scalar _tmp37 = _source_pose[4] - _target_pose[4];
  const Scalar _tmp38 = _tmp37 * source_inverse_range;
  const Scalar _tmp39 = _tmp11 * _tmp25 + _tmp23 * _tmp30 + _tmp34 * _tmp36 + _tmp38;
  const Scalar _tmp40 = 2 * _target_pose[2];
  const Scalar _tmp41 = _target_pose[3] * _tmp40;
  const Scalar _tmp42 = 2 * _target_pose[1];
  const Scalar _tmp43 = _target_pose[0] * _tmp42;
  const Scalar _tmp44 = _tmp41 + _tmp43;
  const Scalar _tmp45 = std::pow(_source_pose[0], Scalar(2));
  const Scalar _tmp46 = -2 * _tmp45;
  const Scalar _tmp47 = _tmp46 + _tmp6 + 1;
  const Scalar _tmp48 = _source_pose[0] * _tmp28;
  const Scalar _tmp49 = -_tmp48;
  const Scalar _tmp50 = _source_pose[1] * _tmp26;
  const Scalar _tmp51 = _tmp49 + _tmp50;
  const Scalar _tmp52 = _tmp31 + _tmp32;
  const Scalar _tmp53 = _tmp10 * _tmp25;
  const Scalar _tmp54 = _source_pose[5] - _target_pose[5];
  const Scalar _tmp55 = _tmp54 * source_inverse_range;
  const Scalar _tmp56 = _tmp23 * _tmp51 + _tmp36 * _tmp47 + _tmp52 * _tmp53 + _tmp55;
  const Scalar _tmp57 = _target_pose[0] * _tmp40;
  const Scalar _tmp58 = _target_pose[3] * _tmp42;
  const Scalar _tmp59 = -_tmp58;
  const Scalar _tmp60 = _tmp57 + _tmp59;
  const Scalar _tmp61 = _tmp46 + _tmp8;
  const Scalar _tmp62 = _tmp48 + _tmp50;
  const Scalar _tmp63 = -_tmp29;
  const Scalar _tmp64 = _tmp27 + _tmp63;
  const Scalar _tmp65 = _source_pose[6] - _target_pose[6];
  const Scalar _tmp66 = _tmp65 * source_inverse_range;
  const Scalar _tmp67 = _tmp23 * _tmp61 + _tmp36 * _tmp62 + _tmp53 * _tmp64 + _tmp66;
  const Scalar _tmp68 = _tmp39 * _tmp4 + _tmp44 * _tmp56 + _tmp60 * _tmp67;
  const Scalar _tmp69 = Scalar(1.0) / (target_calibration_storage(4, 0));
  const Scalar _tmp70 = _tmp69 * target_calibration_storage(0, 0);
  const Scalar _tmp71 = _tmp57 + _tmp58;
  const Scalar _tmp72 = _target_pose[2] * _tmp42;
  const Scalar _tmp73 = 2 * _target_pose[0] * _target_pose[3];
  const Scalar _tmp74 = -_tmp73;
  const Scalar _tmp75 = _tmp72 + _tmp74;
  const Scalar _tmp76 = std::pow(_target_pose[0], Scalar(2));
  const Scalar _tmp77 = 1 - 2 * _tmp76;
  const Scalar _tmp78 = _tmp1 + _tmp77;
  const Scalar _tmp79 = _tmp39 * _tmp71 + _tmp56 * _tmp75 + _tmp67 * _tmp78;
  const Scalar _tmp80 = std::max<Scalar>(epsilon, std::fabs(_tmp79));
  const Scalar _tmp81 = std::pow(_tmp80, Scalar(-2));
  const Scalar _tmp82 = -_tmp41;
  const Scalar _tmp83 = _tmp43 + _tmp82;
  const Scalar _tmp84 = _tmp3 + _tmp77;
  const Scalar _tmp85 = _tmp72 + _tmp73;
  const Scalar _tmp86 = _tmp39 * _tmp83 + _tmp56 * _tmp84 + _tmp67 * _tmp85;
  const Scalar _tmp87 = std::sqrt(Scalar(std::pow(_tmp68, Scalar(2)) * _tmp81 +
                                         _tmp81 * std::pow(_tmp86, Scalar(2)) + epsilon));
  const Scalar _tmp88 = Scalar(0.5) * target_calibration_storage(4, 0);
  const Scalar _tmp89 = std::atan(2 * _tmp87 * std::tan(_tmp88)) / (_tmp80 * _tmp87);
  const Scalar _tmp90 = target_calibration_storage(2, 0) - target_pixel(0, 0);
  const Scalar _tmp91 = _tmp68 * _tmp70 * _tmp89 + _tmp90;
  const Scalar _tmp92 = _tmp69 * target_calibration_storage(1, 0);
  const Scalar _tmp93 = target_calibration_storage(3, 0) - target_pixel(1, 0);
  const Scalar _tmp94 = _tmp86 * _tmp89 * _tmp92 + _tmp93;
  const Scalar _tmp95 = std::pow(_tmp91, Scalar(2)) + std::pow(_tmp94, Scalar(2)) + epsilon;
  const Scalar _tmp96 = Scalar(1.0) / (epsilon - gnc_mu + 1);
  const Scalar _tmp97 = epsilon + std::fabs(_tmp96);
  const Scalar _tmp98 = std::pow(gnc_scale, Scalar(-2));
  const Scalar _tmp99 = _tmp98 / _tmp97;
  const Scalar _tmp100 = 2 - _tmp96;
  const Scalar _tmp101 =
      _tmp100 + epsilon * (2 * std::min<Scalar>(0, (((_tmp100) > 0) - ((_tmp100) < 0))) + 1);
  const Scalar _tmp102 = (Scalar(1) / Scalar(2)) * _tmp101;
  const Scalar _tmp103 = 2 * _tmp97 / _tmp101;
  const Scalar _tmp104 =
      weight * std::max<Scalar>(0, (((-std::fabs(_tmp19) + Scalar(M_PI_2)) > 0) -
                                    ((-std::fabs(_tmp19) + Scalar(M_PI_2)) < 0)));
  const Scalar _tmp105 =
      std::sqrt(_tmp104) *
      std::sqrt(Scalar(_tmp103 * (std::pow(Scalar(_tmp95 * _tmp99 + 1), _tmp102) - 1))) *
      std::sqrt(Scalar(std::max<Scalar>(0, (((_tmp79) > 0) - ((_tmp79) < 0))))) / std::sqrt(_tmp95);
  const Scalar _tmp106 = _tmp105 * _tmp91;
  const Scalar _tmp107 = _tmp105 * _tmp94;
  const Scalar _tmp108 = std::pow(_source_pose[3], Scalar(2));
  const Scalar _tmp109 = -_tmp108;
  const Scalar _tmp110 = -_tmp7;
  const Scalar _tmp111 = std::tan(_tmp14);
  const Scalar _tmp112 = _tmp21 / std::pow(_tmp111, Scalar(2));
  const Scalar _tmp113 =
      std::pow(Scalar(_tmp112 * _tmp13 + _tmp112 * _tmp16 + 1), Scalar(Scalar(-1) / Scalar(2)));
  const Scalar _tmp114 = _tmp113 * _tmp51;
  const Scalar _tmp115 = _tmp24 / _tmp111;
  const Scalar _tmp116 = _tmp115 * _tmp35;
  const Scalar _tmp117 = _tmp113 * (_tmp109 + _tmp110 + _tmp45 + _tmp5) + _tmp114 * _tmp116;
  const Scalar _tmp118 = -_tmp50;
  const Scalar _tmp119 = _tmp108 + _tmp110;
  const Scalar _tmp120 = -_tmp45;
  const Scalar _tmp121 = _tmp120 + _tmp5;
  const Scalar _tmp122 = _tmp113 * _tmp115;
  const Scalar _tmp123 = _tmp122 * _tmp35;
  const Scalar _tmp124 = _tmp113 * (_tmp118 + _tmp49) + _tmp123 * (_tmp119 + _tmp121);
  const Scalar _tmp125 = -_tmp31;
  const Scalar _tmp126 = _tmp113 * _tmp30;
  const Scalar _tmp127 = _tmp113 * (_tmp125 + _tmp32) + _tmp116 * _tmp126;
  const Scalar _tmp128 = _tmp117 * _tmp84 + _tmp124 * _tmp85 + _tmp127 * _tmp83;
  const Scalar _tmp129 = _tmp113 * _tmp52;
  const Scalar _tmp130 = _tmp10 * _tmp115;
  const Scalar _tmp131 = _tmp114 + _tmp123 * _tmp47 + _tmp129 * _tmp130 + _tmp55;
  const Scalar _tmp132 = _tmp11 * _tmp122 + _tmp123 * _tmp34 + _tmp126 + _tmp38;
  const Scalar _tmp133 = _tmp122 * _tmp62;
  const Scalar _tmp134 = _tmp113 * _tmp64;
  const Scalar _tmp135 = _tmp113 * _tmp61 + _tmp130 * _tmp134 + _tmp133 * _tmp35 + _tmp66;
  const Scalar _tmp136 = _tmp132 * _tmp83 + _tmp135 * _tmp85;
  const Scalar _tmp137 = _tmp131 * _tmp84 + _tmp136;
  const Scalar _tmp138 = std::pow(_tmp137, Scalar(2));
  const Scalar _tmp139 = _tmp131 * _tmp75 + _tmp132 * _tmp71;
  const Scalar _tmp140 = _tmp135 * _tmp78 + _tmp139;
  const Scalar _tmp141 = std::fabs(_tmp140);
  const Scalar _tmp142 = std::max<Scalar>(_tmp141, epsilon);
  const Scalar _tmp143 = std::pow(_tmp142, Scalar(-2));
  const Scalar _tmp144 = _tmp131 * _tmp44 + _tmp135 * _tmp60;
  const Scalar _tmp145 = _tmp132 * _tmp4 + _tmp144;
  const Scalar _tmp146 = std::pow(_tmp145, Scalar(2));
  const Scalar _tmp147 = _tmp138 * _tmp143 + _tmp143 * _tmp146 + epsilon;
  const Scalar _tmp148 = std::sqrt(_tmp147);
  const Scalar _tmp149 = Scalar(1.0) / (_tmp148);
  const Scalar _tmp150 = Scalar(1.0) / (_tmp142);
  const Scalar _tmp151 = std::tan(_tmp88);
  const Scalar _tmp152 = std::atan(2 * _tmp148 * _tmp151);
  const Scalar _tmp153 = _tmp150 * _tmp152;
  const Scalar _tmp154 = _tmp149 * _tmp153;
  const Scalar _tmp155 = _tmp154 * _tmp92;
  const Scalar _tmp156 = _tmp117 * _tmp75 + _tmp124 * _tmp78 + _tmp127 * _tmp71;
  const Scalar _tmp157 = _tmp137 * _tmp92;
  const Scalar _tmp158 = (((_tmp140) > 0) - ((_tmp140) < 0));
  const Scalar _tmp159 = _tmp158 * ((((_tmp141 - epsilon) > 0) - ((_tmp141 - epsilon) < 0)) + 1);
  const Scalar _tmp160 = (Scalar(1) / Scalar(2)) * _tmp143 * _tmp149 * _tmp152 * _tmp159;
  const Scalar _tmp161 = _tmp157 * _tmp160;
  const Scalar _tmp162 = 2 * _tmp143;
  const Scalar _tmp163 = _tmp137 * _tmp162;
  const Scalar _tmp164 = _tmp159 / [&]() {
    const Scalar base = _tmp142;
    return base * base * base;
  }();
  const Scalar _tmp165 = _tmp146 * _tmp164;
  const Scalar _tmp166 = _tmp117 * _tmp44 + _tmp124 * _tmp60 + _tmp127 * _tmp4;
  const Scalar _tmp167 = _tmp145 * _tmp162;
  const Scalar _tmp168 = _tmp138 * _tmp164;
  const Scalar _tmp169 =
      _tmp128 * _tmp163 - _tmp156 * _tmp165 - _tmp156 * _tmp168 + _tmp166 * _tmp167;
  const Scalar _tmp170 = (Scalar(1) / Scalar(2)) * _tmp153 / (_tmp147 * std::sqrt(_tmp147));
  const Scalar _tmp171 = _tmp157 * _tmp170;
  const Scalar _tmp172 =
      _tmp150 * _tmp151 / (_tmp147 * (4 * _tmp147 * std::pow(_tmp151, Scalar(2)) + 1));
  const Scalar _tmp173 = _tmp157 * _tmp172;
  const Scalar _tmp174 =
      _tmp128 * _tmp155 - _tmp156 * _tmp161 - _tmp169 * _tmp171 + _tmp169 * _tmp173;
  const Scalar _tmp175 = _tmp137 * _tmp155 + _tmp93;
  const Scalar _tmp176 = 2 * _tmp175;
  const Scalar _tmp177 = _tmp145 * _tmp70;
  const Scalar _tmp178 = _tmp160 * _tmp177;
  const Scalar _tmp179 = _tmp154 * _tmp70;
  const Scalar _tmp180 = _tmp170 * _tmp177;
  const Scalar _tmp181 = _tmp172 * _tmp177;
  const Scalar _tmp182 =
      -_tmp156 * _tmp178 + _tmp166 * _tmp179 - _tmp169 * _tmp180 + _tmp169 * _tmp181;
  const Scalar _tmp183 = _tmp145 * _tmp179 + _tmp90;
  const Scalar _tmp184 = 2 * _tmp183;
  const Scalar _tmp185 = _tmp174 * _tmp176 + _tmp182 * _tmp184;
  const Scalar _tmp186 = std::pow(_tmp175, Scalar(2)) + std::pow(_tmp183, Scalar(2)) + epsilon;
  const Scalar _tmp187 = _tmp186 * _tmp99 + 1;
  const Scalar _tmp188 = std::sqrt(Scalar(_tmp103 * (std::pow(_tmp187, _tmp102) - 1)));
  const Scalar _tmp189 = std::sqrt(_tmp104) * std::sqrt(Scalar(std::max<Scalar>(0, _tmp158)));
  const Scalar _tmp190 = _tmp188 * _tmp189;
  const Scalar _tmp191 = _tmp190 / (_tmp186 * std::sqrt(_tmp186));
  const Scalar _tmp192 = (Scalar(1) / Scalar(2)) * _tmp191;
  const Scalar _tmp193 = _tmp183 * _tmp192;
  const Scalar _tmp194 = std::pow(_tmp186, Scalar(Scalar(-1) / Scalar(2)));
  const Scalar _tmp195 =
      std::pow(_tmp187, Scalar(_tmp102 - 1)) * _tmp189 * _tmp194 * _tmp98 / _tmp188;
  const Scalar _tmp196 = (Scalar(1) / Scalar(2)) * _tmp195;
  const Scalar _tmp197 = _tmp183 * _tmp196;
  const Scalar _tmp198 = _tmp190 * _tmp194;
  const Scalar _tmp199 = _tmp182 * _tmp198 - _tmp185 * _tmp193 + _tmp185 * _tmp197;
  const Scalar _tmp200 = -_tmp5;
  const Scalar _tmp201 = _tmp200 + _tmp45;
  const Scalar _tmp202 = _tmp109 + _tmp7;
  const Scalar _tmp203 = _tmp10 * _tmp122;
  const Scalar _tmp204 = _tmp134 + _tmp203 * (_tmp201 + _tmp202);
  const Scalar _tmp205 = -_tmp27;
  const Scalar _tmp206 = _tmp113 * (_tmp119 + _tmp201) + _tmp203 * (_tmp205 + _tmp63);
  const Scalar _tmp207 = _tmp129 + _tmp203 * (_tmp118 + _tmp48);
  const Scalar _tmp208 = _tmp204 * _tmp85 + _tmp206 * _tmp83 + _tmp207 * _tmp84;
  const Scalar _tmp209 = _tmp204 * _tmp78 + _tmp206 * _tmp71 + _tmp207 * _tmp75;
  const Scalar _tmp210 = _tmp204 * _tmp60 + _tmp206 * _tmp4 + _tmp207 * _tmp44;
  const Scalar _tmp211 =
      _tmp163 * _tmp208 - _tmp165 * _tmp209 + _tmp167 * _tmp210 - _tmp168 * _tmp209;
  const Scalar _tmp212 =
      _tmp155 * _tmp208 - _tmp161 * _tmp209 - _tmp171 * _tmp211 + _tmp173 * _tmp211;
  const Scalar _tmp213 =
      -_tmp178 * _tmp209 + _tmp179 * _tmp210 - _tmp180 * _tmp211 + _tmp181 * _tmp211;
  const Scalar _tmp214 = _tmp176 * _tmp212 + _tmp184 * _tmp213;
  const Scalar _tmp215 = -_tmp193 * _tmp214 + _tmp197 * _tmp214 + _tmp198 * _tmp213;
  const Scalar _tmp216 = _tmp10 * _tmp133 + _tmp123 * (_tmp205 + _tmp29);
  const Scalar _tmp217 = _tmp123 * (_tmp121 + _tmp202) + _tmp203 * _tmp34;
  const Scalar _tmp218 =
      _tmp123 * (_tmp125 + _tmp33) + _tmp203 * (_tmp108 + _tmp120 + _tmp200 + _tmp7);
  const Scalar _tmp219 = _tmp216 * _tmp60 + _tmp217 * _tmp4 + _tmp218 * _tmp44;
  const Scalar _tmp220 = _tmp216 * _tmp78 + _tmp217 * _tmp71 + _tmp218 * _tmp75;
  const Scalar _tmp221 = _tmp216 * _tmp85 + _tmp217 * _tmp83 + _tmp218 * _tmp84;
  const Scalar _tmp222 =
      _tmp163 * _tmp221 - _tmp165 * _tmp220 + _tmp167 * _tmp219 - _tmp168 * _tmp220;
  const Scalar _tmp223 =
      -_tmp178 * _tmp220 + _tmp179 * _tmp219 - _tmp180 * _tmp222 + _tmp181 * _tmp222;
  const Scalar _tmp224 = _tmp157 * _tmp222;
  const Scalar _tmp225 =
      _tmp155 * _tmp221 - _tmp161 * _tmp220 - _tmp170 * _tmp224 + _tmp172 * _tmp224;
  const Scalar _tmp226 = _tmp176 * _tmp225 + _tmp184 * _tmp223;
  const Scalar _tmp227 = -_tmp193 * _tmp226 + _tmp197 * _tmp226 + _tmp198 * _tmp223;
  const Scalar _tmp228 = _tmp161 * source_inverse_range;
  const Scalar _tmp229 = _tmp228 * _tmp71;
  const Scalar _tmp230 = _tmp167 * source_inverse_range;
  const Scalar _tmp231 = _tmp230 * _tmp4;
  const Scalar _tmp232 = _tmp165 * source_inverse_range;
  const Scalar _tmp233 = _tmp232 * _tmp71;
  const Scalar _tmp234 = _tmp163 * source_inverse_range;
  const Scalar _tmp235 = _tmp234 * _tmp83;
  const Scalar _tmp236 = _tmp168 * source_inverse_range;
  const Scalar _tmp237 = _tmp236 * _tmp71;
  const Scalar _tmp238 = _tmp231 - _tmp233 + _tmp235 - _tmp237;
  const Scalar _tmp239 = _tmp155 * source_inverse_range;
  const Scalar _tmp240 = _tmp239 * _tmp83;
  const Scalar _tmp241 = -_tmp171 * _tmp238 + _tmp173 * _tmp238 - _tmp229 + _tmp240;
  const Scalar _tmp242 = _tmp179 * source_inverse_range;
  const Scalar _tmp243 = _tmp242 * _tmp4;
  const Scalar _tmp244 = _tmp178 * source_inverse_range;
  const Scalar _tmp245 = _tmp244 * _tmp71;
  const Scalar _tmp246 = -_tmp180 * _tmp238 + _tmp181 * _tmp238 + _tmp243 - _tmp245;
  const Scalar _tmp247 = _tmp176 * _tmp241 + _tmp184 * _tmp246;
  const Scalar _tmp248 = -_tmp193 * _tmp247 + _tmp197 * _tmp247 + _tmp198 * _tmp246;
  const Scalar _tmp249 = _tmp244 * _tmp75;
  const Scalar _tmp250 = _tmp236 * _tmp75;
  const Scalar _tmp251 = _tmp234 * _tmp84;
  const Scalar _tmp252 = _tmp230 * _tmp44;
  const Scalar _tmp253 = _tmp232 * _tmp75;
  const Scalar _tmp254 = -_tmp250 + _tmp251 + _tmp252 - _tmp253;
  const Scalar _tmp255 = _tmp242 * _tmp44;
  const Scalar _tmp256 = -_tmp180 * _tmp254 + _tmp181 * _tmp254 - _tmp249 + _tmp255;
  const Scalar _tmp257 = _tmp228 * _tmp75;
  const Scalar _tmp258 = _tmp239 * _tmp84;
  const Scalar _tmp259 = -_tmp171 * _tmp254 + _tmp173 * _tmp254 - _tmp257 + _tmp258;
  const Scalar _tmp260 =
      (Scalar(1) / Scalar(2)) * _tmp176 * _tmp259 + (Scalar(1) / Scalar(2)) * _tmp184 * _tmp256;
  const Scalar _tmp261 = _tmp183 * _tmp260;
  const Scalar _tmp262 = -_tmp191 * _tmp261 + _tmp195 * _tmp261 + _tmp198 * _tmp256;
  const Scalar _tmp263 = _tmp242 * _tmp60;
  const Scalar _tmp264 = _tmp244 * _tmp78;
  const Scalar _tmp265 = _tmp230 * _tmp60;
  const Scalar _tmp266 = _tmp234 * _tmp85;
  const Scalar _tmp267 = _tmp236 * _tmp78;
  const Scalar _tmp268 = _tmp232 * _tmp78;
  const Scalar _tmp269 = _tmp265 + _tmp266 - _tmp267 - _tmp268;
  const Scalar _tmp270 = -_tmp180 * _tmp269 + _tmp181 * _tmp269 + _tmp263 - _tmp264;
  const Scalar _tmp271 = _tmp228 * _tmp78;
  const Scalar _tmp272 = _tmp239 * _tmp85;
  const Scalar _tmp273 = -_tmp171 * _tmp269 + _tmp173 * _tmp269 - _tmp271 + _tmp272;
  const Scalar _tmp274 = _tmp176 * _tmp273 + _tmp184 * _tmp270;
  const Scalar _tmp275 = -_tmp193 * _tmp274 + _tmp197 * _tmp274 + _tmp198 * _tmp270;
  const Scalar _tmp276 = -_tmp76;
  const Scalar _tmp277 = std::pow(_target_pose[3], Scalar(2));
  const Scalar _tmp278 = -_tmp0;
  const Scalar _tmp279 = _tmp135 * (_tmp2 + _tmp276 + _tmp277 + _tmp278) + _tmp139;
  const Scalar _tmp280 = _tmp278 + _tmp76;
  const Scalar _tmp281 = -_tmp277;
  const Scalar _tmp282 = _tmp2 + _tmp281;
  const Scalar _tmp283 = -_tmp43;
  const Scalar _tmp284 = -_tmp72;
  const Scalar _tmp285 =
      _tmp131 * (_tmp280 + _tmp282) + _tmp132 * (_tmp283 + _tmp41) + _tmp135 * (_tmp284 + _tmp74);
  const Scalar _tmp286 = _tmp164 * _tmp285;
  const Scalar _tmp287 = -_tmp138 * _tmp286 - _tmp146 * _tmp286 + _tmp163 * _tmp279;
  const Scalar _tmp288 = -_tmp178 * _tmp285 - _tmp180 * _tmp287 + _tmp181 * _tmp287;
  const Scalar _tmp289 =
      _tmp155 * _tmp279 - _tmp161 * _tmp285 - _tmp171 * _tmp287 + _tmp173 * _tmp287;
  const Scalar _tmp290 = _tmp176 * _tmp289 + _tmp184 * _tmp288;
  const Scalar _tmp291 = -_tmp193 * _tmp290 + _tmp197 * _tmp290 + _tmp198 * _tmp288;
  const Scalar _tmp292 = -_tmp2;
  const Scalar _tmp293 = _tmp277 + _tmp292;
  const Scalar _tmp294 = _tmp132 * (_tmp280 + _tmp293) + _tmp144;
  const Scalar _tmp295 = -_tmp57;
  const Scalar _tmp296 = _tmp131 * (_tmp284 + _tmp73) + _tmp132 * (_tmp295 + _tmp59) +
                         _tmp135 * (_tmp0 + _tmp281 + _tmp292 + _tmp76);
  const Scalar _tmp297 = -_tmp165 * _tmp294 + _tmp167 * _tmp296 - _tmp168 * _tmp294;
  const Scalar _tmp298 =
      -_tmp178 * _tmp294 + _tmp179 * _tmp296 - _tmp180 * _tmp297 + _tmp181 * _tmp297;
  const Scalar _tmp299 = -_tmp161 * _tmp294 - _tmp171 * _tmp297 + _tmp173 * _tmp297;
  const Scalar _tmp300 = _tmp176 * _tmp299 + _tmp184 * _tmp298;
  const Scalar _tmp301 = -_tmp193 * _tmp300 + _tmp197 * _tmp300 + _tmp198 * _tmp298;
  const Scalar _tmp302 = _tmp0 + _tmp276;
  const Scalar _tmp303 = _tmp131 * (_tmp293 + _tmp302) + _tmp136;
  const Scalar _tmp304 =
      _tmp131 * (_tmp283 + _tmp82) + _tmp132 * (_tmp282 + _tmp302) + _tmp135 * (_tmp295 + _tmp58);
  const Scalar _tmp305 = _tmp163 * _tmp304 + _tmp167 * _tmp303;
  const Scalar _tmp306 = _tmp179 * _tmp303 - _tmp180 * _tmp305 + _tmp181 * _tmp305;
  const Scalar _tmp307 = _tmp155 * _tmp304 - _tmp171 * _tmp305 + _tmp173 * _tmp305;
  const Scalar _tmp308 = _tmp176 * _tmp307 + _tmp184 * _tmp306;
  const Scalar _tmp309 = -_tmp193 * _tmp308 + _tmp197 * _tmp308 + _tmp198 * _tmp306;
  const Scalar _tmp310 = -_tmp231 + _tmp233 - _tmp235 + _tmp237;
  const Scalar _tmp311 = -_tmp171 * _tmp310 + _tmp173 * _tmp310 + _tmp229 - _tmp240;
  const Scalar _tmp312 = -_tmp180 * _tmp310 + _tmp181 * _tmp310 - _tmp243 + _tmp245;
  const Scalar _tmp313 = _tmp176 * _tmp311 + _tmp184 * _tmp312;
  const Scalar _tmp314 = -_tmp193 * _tmp313 + _tmp197 * _tmp313 + _tmp198 * _tmp312;
  const Scalar _tmp315 = _tmp250 - _tmp251 - _tmp252 + _tmp253;
  const Scalar _tmp316 = -_tmp180 * _tmp315 + _tmp181 * _tmp315 + _tmp249 - _tmp255;
  const Scalar _tmp317 = -_tmp171 * _tmp315 + _tmp173 * _tmp315 + _tmp257 - _tmp258;
  const Scalar _tmp318 = _tmp176 * _tmp317 + _tmp184 * _tmp316;
  const Scalar _tmp319 = -_tmp193 * _tmp318 + _tmp197 * _tmp318 + _tmp198 * _tmp316;
  const Scalar _tmp320 = -_tmp265 - _tmp266 + _tmp267 + _tmp268;
  const Scalar _tmp321 = _tmp177 * _tmp320;
  const Scalar _tmp322 = -_tmp170 * _tmp321 + _tmp172 * _tmp321 - _tmp263 + _tmp264;
  const Scalar _tmp323 = -_tmp171 * _tmp320 + _tmp173 * _tmp320 + _tmp271 - _tmp272;
  const Scalar _tmp324 = _tmp176 * _tmp323 + _tmp184 * _tmp322;
  const Scalar _tmp325 = -_tmp193 * _tmp324 + _tmp197 * _tmp324 + _tmp198 * _tmp322;
  const Scalar _tmp326 = _tmp37 * _tmp71 + _tmp54 * _tmp75 + _tmp65 * _tmp78;
  const Scalar _tmp327 = _tmp37 * _tmp4 + _tmp44 * _tmp54 + _tmp60 * _tmp65;
  const Scalar _tmp328 = _tmp37 * _tmp83 + _tmp54 * _tmp84 + _tmp65 * _tmp85;
  const Scalar _tmp329 =
      _tmp163 * _tmp328 - _tmp165 * _tmp326 + _tmp167 * _tmp327 - _tmp168 * _tmp326;
  const Scalar _tmp330 =
      -_tmp178 * _tmp326 + _tmp179 * _tmp327 - _tmp180 * _tmp329 + _tmp181 * _tmp329;
  const Scalar _tmp331 =
      _tmp155 * _tmp328 - _tmp161 * _tmp326 - _tmp171 * _tmp329 + _tmp173 * _tmp329;
  const Scalar _tmp332 = _tmp176 * _tmp331 + _tmp184 * _tmp330;
  const Scalar _tmp333 = -_tmp193 * _tmp332 + _tmp197 * _tmp332 + _tmp198 * _tmp330;
  const Scalar _tmp334 = _tmp175 * _tmp196;
  const Scalar _tmp335 = _tmp175 * _tmp192;
  const Scalar _tmp336 = _tmp174 * _tmp198 + _tmp185 * _tmp334 - _tmp185 * _tmp335;
  const Scalar _tmp337 = _tmp198 * _tmp212 + _tmp214 * _tmp334 - _tmp214 * _tmp335;
  const Scalar _tmp338 = _tmp198 * _tmp225 + _tmp226 * _tmp334 - _tmp226 * _tmp335;
  const Scalar _tmp339 = _tmp198 * _tmp241 + _tmp247 * _tmp334 - _tmp247 * _tmp335;
  const Scalar _tmp340 = _tmp175 * _tmp260;
  const Scalar _tmp341 = -_tmp191 * _tmp340 + _tmp195 * _tmp340 + _tmp198 * _tmp259;
  const Scalar _tmp342 = _tmp198 * _tmp273 + _tmp274 * _tmp334 - _tmp274 * _tmp335;
  const Scalar _tmp343 = _tmp198 * _tmp289 + _tmp290 * _tmp334 - _tmp290 * _tmp335;
  const Scalar _tmp344 = _tmp198 * _tmp299 + _tmp300 * _tmp334 - _tmp300 * _tmp335;
  const Scalar _tmp345 = _tmp198 * _tmp307 + _tmp308 * _tmp334 - _tmp308 * _tmp335;
  const Scalar _tmp346 = _tmp198 * _tmp311 + _tmp313 * _tmp334 - _tmp313 * _tmp335;
  const Scalar _tmp347 = _tmp198 * _tmp317 + _tmp318 * _tmp334 - _tmp318 * _tmp335;
  const Scalar _tmp348 = _tmp198 * _tmp323 + _tmp324 * _tmp334 - _tmp324 * _tmp335;
  const Scalar _tmp349 = _tmp198 * _tmp331 + _tmp332 * _tmp334 - _tmp332 * _tmp335;

  // Output terms (4)
  if (res != nullptr) {
    Eigen::Matrix<Scalar, 2, 1>& _res = (*res);

    _res(0, 0) = _tmp106;
    _res(1, 0) = _tmp107;
  }

  if (jacobian != nullptr) {
    Eigen::Matrix<Scalar, 2, 13>& _jacobian = (*jacobian);

    _jacobian(0, 0) = _tmp199;
    _jacobian(0, 1) = _tmp215;
    _jacobian(0, 2) = _tmp227;
    _jacobian(0, 3) = _tmp248;
    _jacobian(0, 4) = _tmp262;
    _jacobian(0, 5) = _tmp275;
    _jacobian(0, 6) = _tmp291;
    _jacobian(0, 7) = _tmp301;
    _jacobian(0, 8) = _tmp309;
    _jacobian(0, 9) = _tmp314;
    _jacobian(0, 10) = _tmp319;
    _jacobian(0, 11) = _tmp325;
    _jacobian(0, 12) = _tmp333;
    _jacobian(1, 0) = _tmp336;
    _jacobian(1, 1) = _tmp337;
    _jacobian(1, 2) = _tmp338;
    _jacobian(1, 3) = _tmp339;
    _jacobian(1, 4) = _tmp341;
    _jacobian(1, 5) = _tmp342;
    _jacobian(1, 6) = _tmp343;
    _jacobian(1, 7) = _tmp344;
    _jacobian(1, 8) = _tmp345;
    _jacobian(1, 9) = _tmp346;
    _jacobian(1, 10) = _tmp347;
    _jacobian(1, 11) = _tmp348;
    _jacobian(1, 12) = _tmp349;
  }

  if (hessian != nullptr) {
    Eigen::Matrix<Scalar, 13, 13>& _hessian = (*hessian);

    _hessian(0, 0) = std::pow(_tmp199, Scalar(2)) + std::pow(_tmp336, Scalar(2));
    _hessian(0, 1) = 0;
    _hessian(0, 2) = 0;
    _hessian(0, 3) = 0;
    _hessian(0, 4) = 0;
    _hessian(0, 5) = 0;
    _hessian(0, 6) = 0;
    _hessian(0, 7) = 0;
    _hessian(0, 8) = 0;
    _hessian(0, 9) = 0;
    _hessian(0, 10) = 0;
    _hessian(0, 11) = 0;
    _hessian(0, 12) = 0;
    _hessian(1, 0) = _tmp199 * _tmp215 + _tmp336 * _tmp337;
    _hessian(1, 1) = std::pow(_tmp215, Scalar(2)) + std::pow(_tmp337, Scalar(2));
    _hessian(1, 2) = 0;
    _hessian(1, 3) = 0;
    _hessian(1, 4) = 0;
    _hessian(1, 5) = 0;
    _hessian(1, 6) = 0;
    _hessian(1, 7) = 0;
    _hessian(1, 8) = 0;
    _hessian(1, 9) = 0;
    _hessian(1, 10) = 0;
    _hessian(1, 11) = 0;
    _hessian(1, 12) = 0;
    _hessian(2, 0) = _tmp199 * _tmp227 + _tmp336 * _tmp338;
    _hessian(2, 1) = _tmp215 * _tmp227 + _tmp337 * _tmp338;
    _hessian(2, 2) = std::pow(_tmp227, Scalar(2)) + std::pow(_tmp338, Scalar(2));
    _hessian(2, 3) = 0;
    _hessian(2, 4) = 0;
    _hessian(2, 5) = 0;
    _hessian(2, 6) = 0;
    _hessian(2, 7) = 0;
    _hessian(2, 8) = 0;
    _hessian(2, 9) = 0;
    _hessian(2, 10) = 0;
    _hessian(2, 11) = 0;
    _hessian(2, 12) = 0;
    _hessian(3, 0) = _tmp199 * _tmp248 + _tmp336 * _tmp339;
    _hessian(3, 1) = _tmp215 * _tmp248 + _tmp337 * _tmp339;
    _hessian(3, 2) = _tmp227 * _tmp248 + _tmp338 * _tmp339;
    _hessian(3, 3) = std::pow(_tmp248, Scalar(2)) + std::pow(_tmp339, Scalar(2));
    _hessian(3, 4) = 0;
    _hessian(3, 5) = 0;
    _hessian(3, 6) = 0;
    _hessian(3, 7) = 0;
    _hessian(3, 8) = 0;
    _hessian(3, 9) = 0;
    _hessian(3, 10) = 0;
    _hessian(3, 11) = 0;
    _hessian(3, 12) = 0;
    _hessian(4, 0) = _tmp199 * _tmp262 + _tmp336 * _tmp341;
    _hessian(4, 1) = _tmp215 * _tmp262 + _tmp337 * _tmp341;
    _hessian(4, 2) = _tmp227 * _tmp262 + _tmp338 * _tmp341;
    _hessian(4, 3) = _tmp248 * _tmp262 + _tmp339 * _tmp341;
    _hessian(4, 4) = std::pow(_tmp262, Scalar(2)) + std::pow(_tmp341, Scalar(2));
    _hessian(4, 5) = 0;
    _hessian(4, 6) = 0;
    _hessian(4, 7) = 0;
    _hessian(4, 8) = 0;
    _hessian(4, 9) = 0;
    _hessian(4, 10) = 0;
    _hessian(4, 11) = 0;
    _hessian(4, 12) = 0;
    _hessian(5, 0) = _tmp199 * _tmp275 + _tmp336 * _tmp342;
    _hessian(5, 1) = _tmp215 * _tmp275 + _tmp337 * _tmp342;
    _hessian(5, 2) = _tmp227 * _tmp275 + _tmp338 * _tmp342;
    _hessian(5, 3) = _tmp248 * _tmp275 + _tmp339 * _tmp342;
    _hessian(5, 4) = _tmp262 * _tmp275 + _tmp341 * _tmp342;
    _hessian(5, 5) = std::pow(_tmp275, Scalar(2)) + std::pow(_tmp342, Scalar(2));
    _hessian(5, 6) = 0;
    _hessian(5, 7) = 0;
    _hessian(5, 8) = 0;
    _hessian(5, 9) = 0;
    _hessian(5, 10) = 0;
    _hessian(5, 11) = 0;
    _hessian(5, 12) = 0;
    _hessian(6, 0) = _tmp199 * _tmp291 + _tmp336 * _tmp343;
    _hessian(6, 1) = _tmp215 * _tmp291 + _tmp337 * _tmp343;
    _hessian(6, 2) = _tmp227 * _tmp291 + _tmp338 * _tmp343;
    _hessian(6, 3) = _tmp248 * _tmp291 + _tmp339 * _tmp343;
    _hessian(6, 4) = _tmp262 * _tmp291 + _tmp341 * _tmp343;
    _hessian(6, 5) = _tmp275 * _tmp291 + _tmp342 * _tmp343;
    _hessian(6, 6) = std::pow(_tmp291, Scalar(2)) + std::pow(_tmp343, Scalar(2));
    _hessian(6, 7) = 0;
    _hessian(6, 8) = 0;
    _hessian(6, 9) = 0;
    _hessian(6, 10) = 0;
    _hessian(6, 11) = 0;
    _hessian(6, 12) = 0;
    _hessian(7, 0) = _tmp199 * _tmp301 + _tmp336 * _tmp344;
    _hessian(7, 1) = _tmp215 * _tmp301 + _tmp337 * _tmp344;
    _hessian(7, 2) = _tmp227 * _tmp301 + _tmp338 * _tmp344;
    _hessian(7, 3) = _tmp248 * _tmp301 + _tmp339 * _tmp344;
    _hessian(7, 4) = _tmp262 * _tmp301 + _tmp341 * _tmp344;
    _hessian(7, 5) = _tmp275 * _tmp301 + _tmp342 * _tmp344;
    _hessian(7, 6) = _tmp291 * _tmp301 + _tmp343 * _tmp344;
    _hessian(7, 7) = std::pow(_tmp301, Scalar(2)) + std::pow(_tmp344, Scalar(2));
    _hessian(7, 8) = 0;
    _hessian(7, 9) = 0;
    _hessian(7, 10) = 0;
    _hessian(7, 11) = 0;
    _hessian(7, 12) = 0;
    _hessian(8, 0) = _tmp199 * _tmp309 + _tmp336 * _tmp345;
    _hessian(8, 1) = _tmp215 * _tmp309 + _tmp337 * _tmp345;
    _hessian(8, 2) = _tmp227 * _tmp309 + _tmp338 * _tmp345;
    _hessian(8, 3) = _tmp248 * _tmp309 + _tmp339 * _tmp345;
    _hessian(8, 4) = _tmp262 * _tmp309 + _tmp341 * _tmp345;
    _hessian(8, 5) = _tmp275 * _tmp309 + _tmp342 * _tmp345;
    _hessian(8, 6) = _tmp291 * _tmp309 + _tmp343 * _tmp345;
    _hessian(8, 7) = _tmp301 * _tmp309 + _tmp344 * _tmp345;
    _hessian(8, 8) = std::pow(_tmp309, Scalar(2)) + std::pow(_tmp345, Scalar(2));
    _hessian(8, 9) = 0;
    _hessian(8, 10) = 0;
    _hessian(8, 11) = 0;
    _hessian(8, 12) = 0;
    _hessian(9, 0) = _tmp199 * _tmp314 + _tmp336 * _tmp346;
    _hessian(9, 1) = _tmp215 * _tmp314 + _tmp337 * _tmp346;
    _hessian(9, 2) = _tmp227 * _tmp314 + _tmp338 * _tmp346;
    _hessian(9, 3) = _tmp248 * _tmp314 + _tmp339 * _tmp346;
    _hessian(9, 4) = _tmp262 * _tmp314 + _tmp341 * _tmp346;
    _hessian(9, 5) = _tmp275 * _tmp314 + _tmp342 * _tmp346;
    _hessian(9, 6) = _tmp291 * _tmp314 + _tmp343 * _tmp346;
    _hessian(9, 7) = _tmp301 * _tmp314 + _tmp344 * _tmp346;
    _hessian(9, 8) = _tmp309 * _tmp314 + _tmp345 * _tmp346;
    _hessian(9, 9) = std::pow(_tmp314, Scalar(2)) + std::pow(_tmp346, Scalar(2));
    _hessian(9, 10) = 0;
    _hessian(9, 11) = 0;
    _hessian(9, 12) = 0;
    _hessian(10, 0) = _tmp199 * _tmp319 + _tmp336 * _tmp347;
    _hessian(10, 1) = _tmp215 * _tmp319 + _tmp337 * _tmp347;
    _hessian(10, 2) = _tmp227 * _tmp319 + _tmp338 * _tmp347;
    _hessian(10, 3) = _tmp248 * _tmp319 + _tmp339 * _tmp347;
    _hessian(10, 4) = _tmp262 * _tmp319 + _tmp341 * _tmp347;
    _hessian(10, 5) = _tmp275 * _tmp319 + _tmp342 * _tmp347;
    _hessian(10, 6) = _tmp291 * _tmp319 + _tmp343 * _tmp347;
    _hessian(10, 7) = _tmp301 * _tmp319 + _tmp344 * _tmp347;
    _hessian(10, 8) = _tmp309 * _tmp319 + _tmp345 * _tmp347;
    _hessian(10, 9) = _tmp314 * _tmp319 + _tmp346 * _tmp347;
    _hessian(10, 10) = std::pow(_tmp319, Scalar(2)) + std::pow(_tmp347, Scalar(2));
    _hessian(10, 11) = 0;
    _hessian(10, 12) = 0;
    _hessian(11, 0) = _tmp199 * _tmp325 + _tmp336 * _tmp348;
    _hessian(11, 1) = _tmp215 * _tmp325 + _tmp337 * _tmp348;
    _hessian(11, 2) = _tmp227 * _tmp325 + _tmp338 * _tmp348;
    _hessian(11, 3) = _tmp248 * _tmp325 + _tmp339 * _tmp348;
    _hessian(11, 4) = _tmp262 * _tmp325 + _tmp341 * _tmp348;
    _hessian(11, 5) = _tmp275 * _tmp325 + _tmp342 * _tmp348;
    _hessian(11, 6) = _tmp291 * _tmp325 + _tmp343 * _tmp348;
    _hessian(11, 7) = _tmp301 * _tmp325 + _tmp344 * _tmp348;
    _hessian(11, 8) = _tmp309 * _tmp325 + _tmp345 * _tmp348;
    _hessian(11, 9) = _tmp314 * _tmp325 + _tmp346 * _tmp348;
    _hessian(11, 10) = _tmp319 * _tmp325 + _tmp347 * _tmp348;
    _hessian(11, 11) = std::pow(_tmp325, Scalar(2)) + std::pow(_tmp348, Scalar(2));
    _hessian(11, 12) = 0;
    _hessian(12, 0) = _tmp199 * _tmp333 + _tmp336 * _tmp349;
    _hessian(12, 1) = _tmp215 * _tmp333 + _tmp337 * _tmp349;
    _hessian(12, 2) = _tmp227 * _tmp333 + _tmp338 * _tmp349;
    _hessian(12, 3) = _tmp248 * _tmp333 + _tmp339 * _tmp349;
    _hessian(12, 4) = _tmp262 * _tmp333 + _tmp341 * _tmp349;
    _hessian(12, 5) = _tmp275 * _tmp333 + _tmp342 * _tmp349;
    _hessian(12, 6) = _tmp291 * _tmp333 + _tmp343 * _tmp349;
    _hessian(12, 7) = _tmp301 * _tmp333 + _tmp344 * _tmp349;
    _hessian(12, 8) = _tmp309 * _tmp333 + _tmp345 * _tmp349;
    _hessian(12, 9) = _tmp314 * _tmp333 + _tmp346 * _tmp349;
    _hessian(12, 10) = _tmp319 * _tmp333 + _tmp347 * _tmp349;
    _hessian(12, 11) = _tmp325 * _tmp333 + _tmp348 * _tmp349;
    _hessian(12, 12) = std::pow(_tmp333, Scalar(2)) + std::pow(_tmp349, Scalar(2));
  }

  if (rhs != nullptr) {
    Eigen::Matrix<Scalar, 13, 1>& _rhs = (*rhs);

    _rhs(0, 0) = _tmp106 * _tmp199 + _tmp107 * _tmp336;
    _rhs(1, 0) = _tmp106 * _tmp215 + _tmp107 * _tmp337;
    _rhs(2, 0) = _tmp106 * _tmp227 + _tmp107 * _tmp338;
    _rhs(3, 0) = _tmp106 * _tmp248 + _tmp107 * _tmp339;
    _rhs(4, 0) = _tmp106 * _tmp262 + _tmp107 * _tmp341;
    _rhs(5, 0) = _tmp106 * _tmp275 + _tmp107 * _tmp342;
    _rhs(6, 0) = _tmp106 * _tmp291 + _tmp107 * _tmp343;
    _rhs(7, 0) = _tmp106 * _tmp301 + _tmp107 * _tmp344;
    _rhs(8, 0) = _tmp106 * _tmp309 + _tmp107 * _tmp345;
    _rhs(9, 0) = _tmp106 * _tmp314 + _tmp107 * _tmp346;
    _rhs(10, 0) = _tmp106 * _tmp319 + _tmp107 * _tmp347;
    _rhs(11, 0) = _tmp106 * _tmp325 + _tmp107 * _tmp348;
    _rhs(12, 0) = _tmp106 * _tmp333 + _tmp107 * _tmp349;
  }
}  // NOLINT(readability/fn_size)

// NOLINTNEXTLINE(readability/fn_size)
}  // namespace sym