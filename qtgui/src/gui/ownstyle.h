#ifndef INCLUDED_OWN_STYLE_H
#define INCLUDED_OWN_STYLE_H


namespace gui
{

	template <class STYLE>
	class OwnStyle : public STYLE
	{
	public:
		OwnStyle() : STYLE()
		{
			setScrollBarExtent(11, 11);
		}

	protected:

	};
}

#endif
