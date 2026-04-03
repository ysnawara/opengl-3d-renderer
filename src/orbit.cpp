#include "orbit.h"
#include <cmath>
#include <glm/gtc/constants.hpp>

static constexpr double MU_EARTH = 398600.4418; // km^3/s^2
static constexpr double EARTH_RADIUS = 6371.0;  // km
static constexpr double OMEGA_EARTH = 7.2921159e-5; // rad/s

double solveKepler(double M, double e, double tol, int maxIter) {
    double E = M;
    for (int iter = 0; iter < maxIter; ++iter) {
        double dE = (E - e * std::sin(E) - M) / (1.0 - e * std::cos(E));
        E -= dE;
        if (std::abs(dE) < tol) break;
    }
    return E;
}

glm::dvec3 orbitalToECI(const OrbitalElements& oe, double meanAnomaly) {
    double E = solveKepler(meanAnomaly, oe.e);

    double cosE = std::cos(E);
    double sinE = std::sin(E);
    double nu = std::atan2(std::sqrt(1.0 - oe.e * oe.e) * sinE, cosE - oe.e);

    double r = oe.a * (1.0 - oe.e * cosE);

    double xPerifocal = r * std::cos(nu);
    double yPerifocal = r * std::sin(nu);

    double cosO = std::cos(oe.Omega);
    double sinO = std::sin(oe.Omega);
    double cosw = std::cos(oe.omega);
    double sinw = std::sin(oe.omega);
    double cosi = std::cos(oe.inc);
    double sini = std::sin(oe.inc);

    double xECI = (cosO * cosw - sinO * sinw * cosi) * xPerifocal +
                  (-cosO * sinw - sinO * cosw * cosi) * yPerifocal;
    double yECI = (sinO * cosw + cosO * sinw * cosi) * xPerifocal +
                  (-sinO * sinw + cosO * cosw * cosi) * yPerifocal;
    double zECI = (sinw * sini) * xPerifocal + (cosw * sini) * yPerifocal;

    return glm::dvec3(xECI, zECI, yECI);
}

glm::dvec3 propagate(const OrbitalElements& oe, double timeSinceEpoch) {
    double n = std::sqrt(MU_EARTH / (oe.a * oe.a * oe.a));
    double M = oe.M0 + n * timeSinceEpoch;
    return orbitalToECI(oe, M);
}

std::vector<glm::vec3> computeOrbitPath(const OrbitalElements& oe, int segments,
                                         float visualScale) {
    std::vector<glm::vec3> path;
    path.reserve(segments + 1);

    double period = 2.0 * glm::pi<double>() * std::sqrt(oe.a * oe.a * oe.a / MU_EARTH);

    for (int i = 0; i <= segments; ++i) {
        double t = period * static_cast<double>(i) / segments;
        glm::dvec3 pos = propagate(oe, t);
        path.emplace_back(glm::vec3(pos * static_cast<double>(visualScale / EARTH_RADIUS)));
    }
    return path;
}

glm::vec2 eciToLatLon(const glm::dvec3& eci, double gmst) {
    double x = eci.x;
    double y = eci.z;
    double z = eci.y;

    double r = std::sqrt(x * x + y * y + z * z);
    double lat = std::asin(z / r);
    double lon = std::atan2(y, x) - gmst;

    while (lon > glm::pi<double>()) lon -= 2.0 * glm::pi<double>();
    while (lon < -glm::pi<double>()) lon += 2.0 * glm::pi<double>();

    return glm::vec2(lat, lon);
}

std::vector<glm::vec3> computeGroundTrack(const OrbitalElements& oe,
                                           double startTime, double duration,
                                           int samples, float earthRadius) {
    std::vector<glm::vec3> track;
    track.reserve(samples);

    for (int i = 0; i < samples; ++i) {
        double t = startTime + duration * static_cast<double>(i) / (samples - 1);
        glm::dvec3 eci = propagate(oe, t);
        double gmst = OMEGA_EARTH * t;
        glm::vec2 ll = eciToLatLon(eci, gmst);

        float lat = static_cast<float>(ll.x);
        float lon = static_cast<float>(ll.y);
        float offset = earthRadius * 1.002f;

        track.emplace_back(glm::vec3(
            offset * std::cos(lat) * std::cos(lon),
            offset * std::sin(lat),
            offset * std::cos(lat) * std::sin(lon)
        ));
    }
    return track;
}
