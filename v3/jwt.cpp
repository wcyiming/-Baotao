#include "jwt.h"

jwt::jwt()
{

}

QByteArray jwt::encode_jwt(const QJsonObject &payload, const QByteArray& secret) {
    QByteArray payload_base64 = QByteArray(QJsonDocument(payload).toJson(QJsonDocument::Compact)).toBase64();
    QJsonObject header;
    header.insert("alg","has256");
    header.insert("typ","jwt");
    QByteArray header_base64 = QByteArray(QJsonDocument(header).toJson(QJsonDocument::Compact)).toBase64();
    QByteArray sig = QMessageAuthenticationCode::hash(header_base64 + "." + payload_base64, secret,
                                                      QCryptographicHash::Sha256).toBase64();
    return header_base64 + "." + payload_base64 + "." + sig;
}

bool jwt::verify_jwt(const QByteArray &jwt, const QByteArray &secret) {
    auto l = jwt.split('.');
    assert(l.length() == 3);
    QByteArray header_base64 = l[0];
    QByteArray payload_base64 = l[1];
    QByteArray sig_base64 = l[2];

    QByteArray sig = QMessageAuthenticationCode::hash(header_base64 + "." + payload_base64, secret,
                                                      QCryptographicHash::Sha256).toBase64();
    qDebug()<<QString("id:%1").arg(sig == sig_base64);
    return sig == sig_base64;
}

QJsonObject jwt::decode_jwt(const QByteArray &jwt) {
    auto l = jwt.split('.');
    assert(l.length() == 3);
    QByteArray payload_base64 = QByteArray::fromBase64(l[1]);

    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(payload_base64, &jsonError);
    QJsonObject payload = doucment.object();

    return payload;
}
