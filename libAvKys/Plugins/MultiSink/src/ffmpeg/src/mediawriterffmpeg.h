/* Webcamoid, webcam capture application.
 * Copyright (C) 2016  Gonzalo Exequiel Pedone
 *
 * Webcamoid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Webcamoid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Webcamoid. If not, see <http://www.gnu.org/licenses/>.
 *
 * Web-Site: http://webcamoid.github.io/
 */

#ifndef MEDIAWRITERFFMPEG_H
#define MEDIAWRITERFFMPEG_H

#include "mediawriter.h"

class MediaWriterFFmpegPrivate;
class AkAudioCaps;
class AkVideoCaps;
struct AVPacket;

class MediaWriterFFmpeg: public MediaWriter
{
    Q_OBJECT

    public:
        MediaWriterFFmpeg(QObject *parent=nullptr);
        ~MediaWriterFFmpeg();

        Q_INVOKABLE QString defaultFormat() override;
        Q_INVOKABLE QString outputFormat() const override;
        Q_INVOKABLE QVariantList streams() const override;
        Q_INVOKABLE qint64 maxPacketQueueSize() const override;
        Q_INVOKABLE QStringList supportedFormats() override;
        Q_INVOKABLE QStringList fileExtensions(const QString &format) override;
        Q_INVOKABLE QString formatDescription(const QString &format) override;
        Q_INVOKABLE QVariantList formatOptions() override;
        Q_INVOKABLE QStringList supportedCodecs(const QString &format) override;
        Q_INVOKABLE QStringList supportedCodecs(const QString &format,
                                                AkCaps::CapsType type) override;
        Q_INVOKABLE QString defaultCodec(const QString &format,
                                         AkCaps::CapsType type) override;
        Q_INVOKABLE QString codecDescription(const QString &codec) override;
        Q_INVOKABLE AkCaps::CapsType codecType(const QString &codec) override;
        Q_INVOKABLE QVariantMap defaultCodecParams(const QString &codec) override;
        Q_INVOKABLE QVariantMap addStream(int streamIndex,
                                          const AkCaps &streamCaps) override;
        Q_INVOKABLE QVariantMap addStream(int streamIndex,
                                          const AkCaps &streamCaps,
                                          const QVariantMap &codecParams) override;
        Q_INVOKABLE QVariantMap updateStream(int index) override;
        Q_INVOKABLE QVariantMap updateStream(int index,
                                             const QVariantMap &codecParams) override;
        Q_INVOKABLE QVariantList codecOptions(int index) override;

    private:
        MediaWriterFFmpegPrivate *d;

        AkVideoCaps nearestDVCaps(const AkVideoCaps &caps) const;
        AkVideoCaps nearestDNxHDCaps(const AkVideoCaps &caps) const;
        AkVideoCaps nearestH261Caps(const AkVideoCaps &caps) const;
        AkVideoCaps nearestH263Caps(const AkVideoCaps &caps) const;
        AkVideoCaps nearestGXFCaps(const AkVideoCaps &caps) const;
        AkAudioCaps nearestSWFCaps(const AkAudioCaps &caps) const;

    public slots:
        void setOutputFormat(const QString &outputFormat) override;
        void setFormatOptions(const QVariantMap &formatOptions) override;
        void setCodecOptions(int index, const QVariantMap &codecOptions) override;
        void setMaxPacketQueueSize(qint64 maxPacketQueueSize) override;
        void resetOutputFormat() override;
        void resetFormatOptions() override;
        void resetCodecOptions(int index) override;
        void resetMaxPacketQueueSize() override;
        void enqueuePacket(const AkPacket &packet) override;
        void clearStreams() override;
        bool init() override;
        void uninit() override;

    private slots:
        void writePacket(AVPacket *packet);

    friend class VideoStream;
    friend class AudioStream;
};

#endif // MEDIAWRITERFFMPEG_H
