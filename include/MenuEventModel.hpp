/*
** MenuEventController.hpp for cpp_indie_studio in /home/jabbar_y/rendu/cpp_indie_studio/MenuEventController.hpp
**
** Made by Yassir Jabbari
** Login   <yassir.jabbari@epitech.eu>
**
** Started on  Sat May 06 17:31:42 2017 Yassir Jabbari
// Last update Sat May  6 18:30:54 2017 Jabbari Yassir
*/
#ifndef CPP_INDIE_STUDIO_MENUEVENTCONTROLLER_HPP
#define CPP_INDIE_STUDIO_MENUEVENTCONTROLLER_HPP
# include <irrlicht.h>

class MenuEventModel : public irr::IEventReceiver
{
private:
  irr::s32		selected;
  irr::gui::IGUIButton	*startButton;
  irr::gui::IGUIButton	*optionButton;
  irr::gui::IGUIButton	*exitButton;
  irr::IrrlichtDevice	*device;
  bool			*play;
  
 public:
  MenuEventModel(irr::IrrlichtDevice *device);
  virtual bool OnEvent(const irr::SEvent &event);
  void		setSelected(irr::s32 const &selected);
  void		setStartButton(irr::gui::IGUIButton *startButton);
  void 		setOptionButton(irr::gui::IGUIButton *optionButton);
  void 		setExitButton(irr::gui::IGUIButton *exitButton);
  void		setPlay(bool &);
};
#endif //CPP_INDIE_STUDIO_MENUEVENTCONTROLLER_HPP
