/*
** EPITECH PROJECT, 2026
** my_plumber
** File description:
** constant.hpp
*/

#ifndef CONSTANT_HPP_
    #define CONSTANT_HPP_


    /* MOUVEMENTS HORIZONTAUX*/

    #define MINIMUM_WALK_VELOCITY      0.07421875 * 4
    #define MAXIMUM_WALK_SPEED         1.5625 * 4
    #define WALKING_ACCELERATION       0.037109375 * 4
    #define MAXIMUM_WALK_SPEED_UW      1.0625 * 4
    #define RUNNING_ACCELERATION       0.0556640625 * 4
    #define MAXIMUM_WALK_SPEED_ENTRY   0.8125 * 4
    #define RELEASE_DECELERATION       0.05078125 * 4
    #define MAXIMUM_RUNNING_SPEED      2.5625 * 4
    #define SKIDDING_DECELERATION      0.1015625 * 4
    #define SKID_TURNAROUND_SPEED      0.5625 * 4


    /* MOUVEMENTS VERTICAUX*/

    #define V_L1_UP         -4 * 4
    #define V_L1_DWN_A      0.125 * 4
    #define V_L1_DWN        0.4375 * 4
    #define V_1T24_UP       -4 * 4
    #define V_1T24_DWN_A    0.1171875 * 4
    #define V_1T24_DWN      0.375 * 4
    #define V_25M_UP        -5 * 4
    #define V_25M_DWN_A     0.15625 * 4
    #define V_25M_DWN       0.5625 * 4
    #define V_EN_UP         -0 * 4
    #define V_EN_DWN_A      0.15625 * 4
    #define V_EN_DWN        0.15625 * 4
    #define V_MAX           4.5 * 4
    #define V_OVERFLOW      4.0 * 4

#endif
