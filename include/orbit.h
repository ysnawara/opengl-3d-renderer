#pragma once

#include <vector>
#include <glm/glm.hpp>

struct OrbitalElements {
    double a;      // semi-major axis (km)
    double e;      // eccentricity
    double inc;    // inclination (rad)
    double Omega;  // right ascension of ascending node (rad)
    double omega;  // argument of perigee (rad)
    double M0;     // mean anomaly at epoch (rad)
};

double solveKepler(double M, double e, double tol = 1e-10, int maxIter = 100);

glm::dvec3 orbitalToECI(const OrbitalElements& oe, double meanAnomaly);

glm::dvec3 propagate(const OrbitalElements& oe, double timeSinceEpoch);

std::vector<glm::vec3> computeOrbitPath(const OrbitalElements& oe, int segments,
                                         float visualScale);

glm::vec2 eciToLatLon(const glm::dvec3& eci, double gmst);

std::vector<glm::vec3> computeGroundTrack(const OrbitalElements& oe,
                                           double startTime, double duration,
                                           int samples, float earthRadius);
