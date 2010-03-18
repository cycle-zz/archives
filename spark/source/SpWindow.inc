//******************************************************************************
inline SpWindow* SpWindow::current()
{
    return ms_pkWindow;
}
//******************************************************************************
inline char* SpWindow::title()
{
    return m_acWindowTitle;
}
//******************************************************************************
inline unsigned int SpWindow::x()
{
    return m_iX;
}
//******************************************************************************
inline unsigned int SpWindow::y()
{
    return m_iY;
}
//******************************************************************************
inline unsigned int SpWindow::width()
{
    return m_iWidth;
}
//******************************************************************************
inline unsigned int SpWindow::height()
{
    return m_iHeight;
}
//******************************************************************************
inline const SpColor4f& SpWindow::bg()
{
    return m_kBgColor;
}
//******************************************************************************
inline void SpWindow::setWindowId(int iSpWindowID)
{
    m_iSpWindowID = iSpWindowID;
}
//******************************************************************************
inline int SpWindow::id()
{
    return m_iSpWindowID;
}
//******************************************************************************
inline SpTimer& SpWindow::timer()
{
	return m_kTimer;
}
//******************************************************************************
