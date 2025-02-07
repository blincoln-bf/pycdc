#include "pyc_code.h"
#include "pyc_module.h"
#include "data.h"

void PycCode::load(PycData* stream, PycModule* mod, int currentDepth, int maxDepth)
{
    if (mod->verCompare(1, 3) >= 0 && mod->verCompare(2, 3) < 0)
	{
        m_argCount = stream->get16();
	}
    else if (mod->verCompare(2, 3) >= 0)
	{
        m_argCount = stream->get32();
	}

    if (mod->verCompare(3, 8) >= 0)
	{
        m_posOnlyArgCount = stream->get32();
	}
    else
	{
        m_posOnlyArgCount = 0;
	}

    if (mod->majorVer() >= 3)
	{
        m_kwOnlyArgCount = stream->get32();
	}
    else
	{
        m_kwOnlyArgCount = 0;
	}

    if (mod->verCompare(1, 3) >= 0 && mod->verCompare(2, 3) < 0)
	{
        m_numLocals = stream->get16();
	}
    else if (mod->verCompare(2, 3) >= 0)
	{
        m_numLocals = stream->get32();
	}
    else
	{
        m_numLocals = 0;
	}

    if (mod->verCompare(1, 5) >= 0 && mod->verCompare(2, 3) < 0)
	{
        m_stackSize = stream->get16();
	}
    else if (mod->verCompare(2, 3) >= 0)
	{
        m_stackSize = stream->get32();
	}
    else
	{
        m_stackSize = 0;
	}

    if (mod->verCompare(1, 3) >= 0 && mod->verCompare(2, 3) < 0)
	{
        m_flags = stream->get16();
	}
    else if (mod->verCompare(2, 3) >= 0)
	{
        m_flags = stream->get32();
	}
    else
	{
        m_flags = 0;
	}
    
	if (CheckRecursionDepth(currentDepth, maxDepth))
	{
		m_code = LoadObject(stream, mod, currentDepth + 1, maxDepth).require_cast<PycString>();
		m_consts = LoadObject(stream, mod, currentDepth + 1, maxDepth).require_cast<PycSequence>();
		m_names = LoadObject(stream, mod, currentDepth + 1, maxDepth).require_cast<PycSequence>();
	}
	else
	{
		m_code = new PycString;
		m_consts = new PycTuple;
		m_names = new PycTuple;
	}

    if ((mod->verCompare(1, 3) >= 0) && CheckRecursionDepth(currentDepth, maxDepth))
	{
        m_varNames = LoadObject(stream, mod, currentDepth + 1, maxDepth).require_cast<PycSequence>();
	}
    else
	{
        m_varNames = new PycTuple;
	}

    if ((mod->verCompare(2, 1) >= 0) && CheckRecursionDepth(currentDepth, maxDepth))
	{
        m_freeVars = LoadObject(stream, mod, currentDepth + 1, maxDepth).require_cast<PycSequence>();
	}
    else
	{
        m_freeVars = new PycTuple;
	}

    if ((mod->verCompare(2, 1) >= 0) && CheckRecursionDepth(currentDepth, maxDepth))
	{
        m_cellVars = LoadObject(stream, mod, currentDepth + 1, maxDepth).require_cast<PycSequence>();
	}
    else
	{
        m_cellVars = new PycTuple;
	}

	if (CheckRecursionDepth(currentDepth, maxDepth))
	{
		m_fileName = LoadObject(stream, mod, currentDepth + 1, maxDepth).require_cast<PycString>();
		m_name = LoadObject(stream, mod, currentDepth + 1, maxDepth).require_cast<PycString>();
	}
	else
	{
		m_fileName = new PycString;
		m_name = new PycString;
	}

    if (mod->verCompare(1, 5) >= 0 && mod->verCompare(2, 3) < 0)
	{
        m_firstLine = stream->get16();
	}
    else if (mod->verCompare(2, 3) >= 0)
	{
        m_firstLine = stream->get32();
	}

    if ((mod->verCompare(1, 5) >= 0) && CheckRecursionDepth(currentDepth, maxDepth))
	{
        m_lnTable = LoadObject(stream, mod, currentDepth + 1, maxDepth).require_cast<PycString>();
	}
    else
	{
        m_lnTable = new PycString;
	}
}
