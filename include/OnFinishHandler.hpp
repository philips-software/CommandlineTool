#pragma once


namespace CommandlineTool
{
	/*
		Handles the finishing process..
	*/
	class  OnFinishHandler
	{
	public:
		virtual ~OnFinishHandler() {}
		/*
			Allows the user to finalize before exiting.
		*/
		virtual void OnFinish() {}
	};
}