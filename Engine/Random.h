#pragma once
#include <cstdlib>

namespace nu {
	inline int RandomInt() {
		return rand();
	}
	/// <summary>
	/// Get Random Integer between 0 and max (exclusive)
	/// </summary>
	/// <param name="max">Exclusive Max</param>
	/// <returns>Returns random number between 0 and max (exclusive)</returns>
	inline int RandomInt(int max) {
		return rand() % max;
	}

	/// <summary>
	/// Get Random Integer between min and max (exclusive)
	/// </summary>
	/// <param name="min">The smallest number it will return</param>
	/// <param name="max">Exclusive Max</param>
	/// <returns>Returns random number between min and max</returns>
	inline int RandomInt(int min, int max) {
		return min + RandomInt(max - min);
	}

	inline float RandomFloat() {
		return rand() / (float)RAND_MAX;
	}
	/// <summary>
	/// Get Random Float between 0 and max (exclusive)
	/// </summary>
	/// <param name="max">Exclusive Max</param>
	/// <returns>Returns a Random Float between 0 and max</returns>
	inline float RandomFloat(float max) {
		return RandomFloat() * max;
	}

	/// <summary>
	/// Get Random Float between min and max (exclusive)
	/// </summary>
	/// <param name="min">The smallest number it will return</param>
	/// <param name="max">Exclusive Max</param>
	/// <returns>Returns a Random Float between min and max</returns>
	inline float RandomFloat(float min, float max) {
		return min + RandomFloat() * (max - min);
	}
}

