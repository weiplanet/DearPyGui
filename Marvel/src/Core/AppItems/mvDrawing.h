#pragma once

#include "Core/AppItems/mvTypeBases.h"

//-----------------------------------------------------------------------------
// Widget Index
//
//     * mvDrawing
//
//-----------------------------------------------------------------------------

#define MV_DRAWCOMMAND_TYPE(x) virtual mvDrawingCommandType getType() const override { return x; }\
virtual void draw(mvDrawing* draw, ImDrawList* draw_list) override;

namespace Marvel {

	class mvDrawing;

	//-----------------------------------------------------------------------------
	// Enums
	//-----------------------------------------------------------------------------
	enum class mvDrawingCommandType
	{
		DrawLine, DrawTriangle, DrawCircle, DrawText, DrawRect, DrawQuad,
		DrawPolyline, DrawBezierCurve, DrawPolygon, DrawImage
	};

	//-----------------------------------------------------------------------------
	// mvDrawingCommand
	//-----------------------------------------------------------------------------
	class mvDrawingCommand
	{

	public:

		virtual ~mvDrawingCommand() = default;
		virtual void draw(mvDrawing* drawing, ImDrawList* draw_list) = 0;
		virtual mvDrawingCommandType getType() const = 0;

		std::string tag = "";

	};

	//-----------------------------------------------------------------------------
	// mvDrawImageCommand
	//-----------------------------------------------------------------------------
	class mvDrawImageCommand : public mvDrawingCommand
	{

	public:

		MV_DRAWCOMMAND_TYPE(mvDrawingCommandType::DrawImage)

		mvDrawImageCommand(const std::string& file, const mvVec2& pmin, const mvVec2& pmax, const mvVec2& uv_min = { 0, 0 },
				const mvVec2& uv_max = { 1, 1 }, const mvColor& color = { 255, 255, 255, 255 })
			: mvDrawingCommand(), m_file(file), m_pmax(pmax), m_pmin(pmin), m_uv_min(uv_min), m_uv_max(uv_max),
			m_color(color)
		{
			if (m_pmax.x < 0 && m_pmax.y < 0)
				m_autosize = true;
		}

	private:

		std::string m_file;
		mvVec2		m_pmax;
		mvVec2		m_pmin;
		mvVec2		m_uv_min;
		mvVec2		m_uv_max;
		mvColor		m_color;
		void*       m_texture = nullptr;
		int         m_width;
		int         m_height;
		bool        m_autosize = false;

	};

	//-----------------------------------------------------------------------------
	// mvDrawLineCommand
	//-----------------------------------------------------------------------------
	class mvDrawLineCommand : public mvDrawingCommand
	{

	public:

		MV_DRAWCOMMAND_TYPE(mvDrawingCommandType::DrawLine)

		mvDrawLineCommand(const mvVec2& p1, const mvVec2& p2, const mvColor& color, float thickness)
			: mvDrawingCommand(), m_p1(p1), m_p2(p2), m_color(color), m_thickness(thickness)
		{
		}

	private:

		mvVec2  m_p1;
		mvVec2  m_p2;
		mvColor m_color;
		float   m_thickness;

	};

	//-----------------------------------------------------------------------------
	// mvDrawTriangleCommand
	//-----------------------------------------------------------------------------
	class mvDrawTriangleCommand : public mvDrawingCommand
	{

	public:

		MV_DRAWCOMMAND_TYPE(mvDrawingCommandType::DrawTriangle)

		mvDrawTriangleCommand(const mvVec2& p1, const mvVec2& p2, const mvVec2& p3, const mvColor& color, float thickness, const mvColor& fill)
			: mvDrawingCommand(), m_p1(p1), m_p2(p2), m_p3(p3), m_color(color), m_fill(fill), m_thickness(thickness)
		{
		}

	private:

		mvVec2  m_p1;
		mvVec2  m_p2;
		mvVec2  m_p3;
		mvColor m_color;
		mvColor m_fill;
		float   m_thickness;

	};

	//-----------------------------------------------------------------------------
	// mvDrawCircleCommand
	//-----------------------------------------------------------------------------
	class mvDrawCircleCommand : public mvDrawingCommand
	{

	public:

		MV_DRAWCOMMAND_TYPE(mvDrawingCommandType::DrawCircle)

		mvDrawCircleCommand(const mvVec2& center, float radius, const mvColor& color, int segments, float thickness, const mvColor& fill)
			: mvDrawingCommand(), m_center(center), m_radius(radius), m_segments(segments), m_color(color), m_fill(fill), m_thickness(thickness)
		{
		}

	private:

		mvVec2  m_center;
		float   m_radius;
		int     m_segments;
		mvColor m_color;
		mvColor m_fill;
		float   m_thickness;

	};

	//-----------------------------------------------------------------------------
	// mvDrawTextCommand
	//-----------------------------------------------------------------------------
	class mvDrawTextCommand : public mvDrawingCommand
	{

	public:

		MV_DRAWCOMMAND_TYPE(mvDrawingCommandType::DrawText)

		mvDrawTextCommand(const mvVec2& pos, const std::string& text, const mvColor& color, int size)
			: mvDrawingCommand(), m_pos(pos), m_text(text), m_color(color), m_size(size)
		{
		}

	private:

		mvVec2      m_pos;
		std::string m_text;
		mvColor     m_color;
		int         m_size;


	};

	//-----------------------------------------------------------------------------
	// mvDrawRectCommand
	//-----------------------------------------------------------------------------
	class mvDrawRectCommand : public mvDrawingCommand
	{

	public:

		MV_DRAWCOMMAND_TYPE(mvDrawingCommandType::DrawRect)

		mvDrawRectCommand(const mvVec2& pmin, const mvVec2& pmax, const mvColor& color, const mvColor& fill, float rounding, float thickness)
			: mvDrawingCommand(), m_pmin(pmin), m_pmax(pmax), m_rounding(rounding), m_color(color),m_fill(fill), m_thickness(thickness)
		{
		}

	private:

		mvVec2  m_pmin;
		mvVec2  m_pmax;
		float   m_rounding;
		mvColor m_color;
		mvColor m_fill;
		float   m_thickness;


	};

	//-----------------------------------------------------------------------------
	// mvDrawQuadCommand
	//-----------------------------------------------------------------------------
	class mvDrawQuadCommand : public mvDrawingCommand
	{

	public:

		MV_DRAWCOMMAND_TYPE(mvDrawingCommandType::DrawQuad)

		mvDrawQuadCommand(const mvVec2& p1, const mvVec2& p2, const mvVec2& p3, const mvVec2& p4,const mvColor& color, const mvColor& fill, float thickness)
			: mvDrawingCommand(), m_p1(p1), m_p2(p2), m_p3(p3), m_p4(p4), m_color(color),m_fill(fill), m_thickness(thickness)
		{
		}

	private:

		mvVec2  m_p1;
		mvVec2  m_p2;
		mvVec2  m_p3;
		mvVec2  m_p4;
		mvColor m_color;
		mvColor m_fill;
		float   m_thickness;


	};

	//-----------------------------------------------------------------------------
	// mvDrawPolylineCommand
	//-----------------------------------------------------------------------------
	class mvDrawPolylineCommand : public mvDrawingCommand
	{

	public:

		MV_DRAWCOMMAND_TYPE(mvDrawingCommandType::DrawPolyline)

		mvDrawPolylineCommand(const std::vector<mvVec2>& points, const mvColor& color, bool closed, float thickness)
			: mvDrawingCommand(), m_points(points), m_color(color), m_closed(closed),m_thickness(thickness)
		{
		}

	private:

		std::vector<mvVec2> m_points;
		mvColor             m_color;
		bool                m_closed;
		float               m_thickness;


	};

	//-----------------------------------------------------------------------------
	// mvDrawPolygonCommand
	//-----------------------------------------------------------------------------
	class mvDrawPolygonCommand : public mvDrawingCommand
	{

	public:

		MV_DRAWCOMMAND_TYPE(mvDrawingCommandType::DrawPolygon)

		mvDrawPolygonCommand(const std::vector<mvVec2>& points, const mvColor& color, const mvColor& fill, float thickness)
			: mvDrawingCommand(), m_points(points), m_color(color), m_fill(fill), m_thickness(thickness)
		{
		}

	private:

		std::vector<mvVec2> m_points;
		mvColor             m_color;
		mvColor             m_fill;
		float               m_thickness;


	};

	//-----------------------------------------------------------------------------
	// mvDrawBezierCurveCommand
	//-----------------------------------------------------------------------------
	class mvDrawBezierCurveCommand : public mvDrawingCommand
	{

	public:

		MV_DRAWCOMMAND_TYPE(mvDrawingCommandType::DrawBezierCurve)

		mvDrawBezierCurveCommand(const mvVec2& p1, const mvVec2& p2, const mvVec2& p3, const mvVec2& p4,const mvColor& color, float thickness, int segments)
			: mvDrawingCommand(), m_p1(p1), m_p2(p2), m_p3(p3), m_p4(p4), m_color(color),m_thickness(thickness), m_segments(segments)
		{
		}

	private:

		mvVec2  m_p1;
		mvVec2  m_p2;
		mvVec2  m_p3;
		mvVec2  m_p4;
		mvColor m_color;
		float   m_thickness;
		int     m_segments;
	};

	//-----------------------------------------------------------------------------
	// mvDrawing
	//-----------------------------------------------------------------------------
	class mvDrawing : public mvNoneItemBase
	{

	public:

		MV_APPITEM_TYPE(mvAppItemType::Drawing)

		mvDrawing(const std::string& parent, const std::string& name, int width, int height)
			: mvNoneItemBase(parent, name)
		{
			m_width = width;
			m_height = height;
		}

		virtual void draw() override;
		virtual void clear();

		inline float  getStartX() const { return m_startx; }
		inline float  getStartY() const { return m_starty; }
		inline mvVec2 getStart () const { return { m_startx, m_starty }; }

		void drawLine       (const mvVec2& p1, const mvVec2& p2, const mvColor& color, float thickness, const std::string& tag = "");
		void drawTriangle   (const mvVec2& p1, const mvVec2& p2, const mvVec2& p3, const mvColor& color, const mvColor& fill, float thickness, const std::string& tag = "");
		void drawRectangle  (const mvVec2& pmin, const mvVec2& pmax, const mvColor& color,const mvColor& fill, float rounding, float thickness, const std::string& tag = "");
		void drawQuad       (const mvVec2& p1, const mvVec2& p2, const mvVec2& p3, const mvVec2& p4,const mvColor& color, const mvColor& fill, float thickness, const std::string& tag = "");
		void drawText       (const mvVec2& pos, const std::string& text, const mvColor& color, int size, const std::string& tag = "");
		void drawCircle     (const mvVec2& center, float radius, const mvColor& color,int segments, float thickness, const mvColor& fill, const std::string& tag = "");
		void drawPolyline   (const std::vector<mvVec2>& points, const mvColor& color, bool closed, float thickness, const std::string& tag = "");
		void drawPolygon    (const std::vector<mvVec2>& points, const mvColor& color, const mvColor& fill, float thickness, const std::string& tag = "");
		void drawBezierCurve(const mvVec2& p1, const mvVec2& p2, const mvVec2& p3, const mvVec2& p4, const mvColor& color, float thickness, int segments, const std::string& tag = "");
		void drawImage      (const std::string& file, const mvVec2& pmin, const mvVec2& pmax, const mvVec2& uv_min, const mvVec2& uv_max, const mvColor& color, const std::string& tag = "");

	private:

		std::vector<mvDrawingCommand*> m_commands;
		ImDrawList* draw_list = nullptr;
		float       m_startx = 0.0f;
		float       m_starty = 0.0f;

	};
}