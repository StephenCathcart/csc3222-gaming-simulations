#ifndef PATHS_H
#define PATHS_H

#include <string>

using std::string;

/// <summary>
/// Stores the path strings to all resources.
/// </summary>
class Paths {
public:
	~Paths(void);

	/** OBJ **/
	static const string OBJ_BALL;
	static const string OBJ_PLANE_FRONT;
	static const string OBJ_PLANE_BACK;
	static const string OBJ_PLANE_LEFT;
	static const string OBJ_PLANE_RIGHT;
	static const string OBJ_PLANE_TOP;
	static const string OBJ_PLANE_BOTTOM;

	/** SHADERS **/
	static const string SHADER_VERT_BALL;
	static const string SHADER_FRAG_BALL;
	static const string SHADER_VERT_PLANE;
	static const string SHADER_FRAG_PLANE;

	/** SHADERS NAMES**/
	static const string SHADER_BALL;
	static const string SHADER_PLANE;

	/** FONTS **/
	static const string FONT_ARIAL;

private:
	Paths(void);
};

#endif