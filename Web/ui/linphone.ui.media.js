/*
 Linphone Web - Web plugin of Linphone an audio/video SIP phone
 Copyright (C) 2012  Yann Diorcet <yann.diorcet@linphone.org>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

/*globals jQuery,linphone*/

linphone.ui.media = {
	// Original function by Alien51
	unique : function(arrVal) {
		var uniqueArr = [];
		for ( var i = arrVal.length; i--;) {
			var val = arrVal[i];
			if (jQuery.inArray(val, uniqueArr) === -1) {
				uniqueArr.unshift(val);
			}
		}
		return uniqueArr;
	},
	updateMediaList : function(target) {
		var base = linphone.ui.getBase(target);
		var core = linphone.ui.getCore(target);

		// Remove JQuery UI select style
		base.find('.window .media-options .ring_device').selectmenu('destroy');
		base.find('.window .media-options .playback_device').selectmenu('destroy');
		base.find('.window .media-options .capture_device').selectmenu('destroy');
		base.find('.window .media-options .video_device').selectmenu('destroy');
		
		// Clear
		base.find('.window .media-options .playback_device').empty();
		base.find('.window .media-options .ring_device').empty();
		base.find('.window .media-options .capture_device').empty();
		base.find('.window .media-options .video_device').empty();

		
		// Sound
		var sound_devices = core.soundDevices;
		for ( var sound_index in sound_devices) {
			var sound_device = sound_devices[sound_index];
			var sound_option = '<option value="' + sound_device + '">' + sound_device + '</option>';
			if (core.soundDeviceCanCapture(sound_device)) {
				base.find('.window .media-options .capture_device').append(sound_option);
			}
			if (core.soundDeviceCanPlayback(sound_device)) {
				base.find('.window .media-options .playback_device').append(sound_option);
				base.find('.window .media-options .ring_device').append(sound_option);
			}
		}

		var selected_ringer_device = core.ringerDevice;
		var selected_playback_device = core.playbackDevice;
		var selected_capture_device = core.captureDevice;
		
		// Log
		linphone.core.log('Ringer device: ' + selected_ringer_device);
		linphone.core.log('Playback device: ' + selected_playback_device);
		linphone.core.log('Capture device: ' + selected_capture_device);
		
		base.find('.window .media-options .ring_device').val(selected_ringer_device);
		base.find('.window .media-options .playback_device').val(selected_playback_device);
		base.find('.window .media-options .capture_device').val(selected_capture_device);

		// Video
		var video_devices = linphone.ui.media.unique(core.videoDevices);
		for ( var video_index in video_devices) {
			var video_device = video_devices[video_index];
			var video_option = '<option value="' + video_device + '">' + video_device + '</option>';
			base.find('.window .media-options .video_device').append(video_option);
		}
		
		var selected_video_device = core.videoDevice;
		
		// Log
		linphone.core.log('Video device: ' + selected_video_device);
		
		base.find('.window .media-options .video_device').val(selected_video_device);
		
		// Apply JQuery UI select style
		base.find('.window .media-options .ring_device').selectmenu();
		base.find('.window .media-options .playback_device').selectmenu();
		base.find('.window .media-options .capture_device').selectmenu();
		base.find('.window .media-options .video_device').selectmenu();
		
		// Event
		base.find('.window .media-options .ring_device').unbind('change');
		base.find('.window .media-options .playback_device').unbind('change');
		base.find('.window .media-options .capture_device').unbind('change');
		base.find('.window .media-options .video_device').unbind('change');
		base.find('.window .media-options .ring_device').change(linphone.ui.media.changeEvent);
		base.find('.window .media-options .playback_device').change(linphone.ui.media.changeEvent);
		base.find('.window .media-options .capture_device').change(linphone.ui.media.changeEvent);
		base.find('.window .media-options .video_device').change(linphone.ui.media.changeEvent);
	},
	changeEvent: function(event) {
		var target = jQuery(event.target ? event.target : event.srcElement);
		var core = linphone.ui.getCore(target);
		if(target.is('.linphone .window .media-options .ring_device')) {
			core.ringerDevice = target.val();
		}
		
		if(target.is('.linphone .window .media-options .playback_device')) {
			core.playbackDevice = target.val();
		}
		
		if(target.is('.linphone .window .media-options .capture_device')) {
			core.captureDevice = target.val();
		}
		
		if(target.is('.linphone .window .media-options .video_device')) {
			core.videoDevice = target.val();
		}
	}
};

// Click
jQuery('html').click(function(event) {
	var target = jQuery(event.target ? event.target : event.srcElement);
	var base = linphone.ui.getBase(target);

	// Click on media item
	if (target.isOrParent('.linphone .window .tools .media > a')) {
		base.find('.window .tools .settings-menu').fadeOut('fast');

		linphone.ui.media.updateMediaList(target);

		base.find('.window .media-options').fadeIn('fast');
	}
});
