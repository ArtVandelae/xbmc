/*
 *      Copyright (C) 2005-2011 Team XBMC
 *      http://www.xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#include "MusicInfoTagLoaderTagLib.h"
#include "MusicInfoTag.h"
#include "utils/log.h"
#include <taglib/fileref.h>
#include <taglib/tag.h>

using namespace MUSIC_INFO;

CMusicInfoTagLoaderTagLib::CMusicInfoTagLoaderTagLib(void)
{}

CMusicInfoTagLoaderTagLib::~CMusicInfoTagLoaderTagLib()
{}

bool CMusicInfoTagLoaderTagLib::SupportsFormat(const CStdString& strExtension)
{
  return  (
    strExtension == "mp3"       ||
    strExtension == "mpc"       ||
    strExtension == "flac"      ||
    strExtension == "mp4"       ||
    strExtension == "m4a"       ||
    strExtension == "asf"       ||
    strExtension == "aiff"      ||
    strExtension == "aif"       ||
    strExtension == "wav"       ||
    strExtension == "tta"       ||
    strExtension == "wv"        ||
    strExtension == "ogg"       ||
    strExtension == "oga"       ||
    strExtension == "oggstream" ||
    strExtension == "spx"       ||
    strExtension == "speex"     ||
    strExtension == "wma"

  );
}

bool CMusicInfoTagLoaderTagLib::Load(const CStdString& strFileName, CMusicInfoTag& tag)
{
  TagLib::FileRef f(strFileName, true, TagLib::AudioProperties::Accurate);
  if (f.isNull())
    return false;

  tag.SetURL(strFileName);
  TagLib::AudioProperties *ap = f.audioProperties();
  TagLib::Tag             *t  = f.tag();

  if (ap)
  {
    tag.SetDuration(ap->length());
  }

  if (t)
  {
    tag.SetTitle      (t->title  ().toCString());
    tag.SetArtist     (t->artist ().toCString());
    tag.SetAlbum      (t->album  ().toCString());
    tag.SetComment    (t->comment().toCString());
    tag.SetGenre      (t->genre  ().toCString());
    tag.SetYear       ((int)t->year());
    tag.SetTrackNumber((int)t->track());
  }

  return true;
}

