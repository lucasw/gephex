/****************************************************************************
** gui::DllSelectorDialog meta object code from reading C++ file 'dllselectordialog.h'
**
** Created: Tue Dec 16 01:19:33 2003
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.2.1   edited Aug 20 15:04 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "dllselectordialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *gui::DllSelectorDialog::className() const
{
    return "gui::DllSelectorDialog";
}

QMetaObject *gui::DllSelectorDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_gui__DllSelectorDialog( "gui::DllSelectorDialog", &gui::DllSelectorDialog::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString gui::DllSelectorDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "gui::DllSelectorDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString gui::DllSelectorDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "gui::DllSelectorDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* gui::DllSelectorDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "r", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"done", 1, param_slot_0 };
    static const QUMethod slot_1 = {"accept", 0, 0 };
    static const QUMethod slot_2 = {"reject", 0, 0 };
    static const QUMethod slot_3 = {"loadModuleClass", 0, 0 };
    static const QUMethod slot_4 = {"unloadModuleClass", 0, 0 };
    static const QUParameter param_slot_5[] = {
	{ "_show", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"setShown", 1, param_slot_5 };
    static const QMetaData slot_tbl[] = {
	{ "done(int)", &slot_0, QMetaData::Protected },
	{ "accept()", &slot_1, QMetaData::Protected },
	{ "reject()", &slot_2, QMetaData::Protected },
	{ "loadModuleClass()", &slot_3, QMetaData::Private },
	{ "unloadModuleClass()", &slot_4, QMetaData::Private },
	{ "setShown(bool)", &slot_5, QMetaData::Private }
    };
    static const QUParameter param_signal_0[] = {
	{ "s", &static_QUType_ptr, "std::string", QUParameter::In }
    };
    static const QUMethod signal_0 = {"status", 1, param_signal_0 };
    static const QUMethod signal_1 = {"closed", 0, 0 };
    static const QMetaData signal_tbl[] = {
	{ "status(const std::string&)", &signal_0, QMetaData::Public },
	{ "closed()", &signal_1, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"gui::DllSelectorDialog", parentObject,
	slot_tbl, 6,
	signal_tbl, 2,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_gui__DllSelectorDialog.setMetaObject( metaObj );
    return metaObj;
}

void* gui::DllSelectorDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "gui::DllSelectorDialog" ) )
	return this;
    if ( !qstrcmp( clname, "IModuleClassNameReceiver" ) )
	return (IModuleClassNameReceiver*)this;
    if ( !qstrcmp( clname, "IModuleClassView" ) )
	return (IModuleClassView*)this;
    return QDialog::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL status
void gui::DllSelectorDialog::status( const std::string& t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 0 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_ptr.set(o+1,&t0);
    activate_signal( clist, o );
}

// SIGNAL closed
void gui::DllSelectorDialog::closed()
{
    activate_signal( staticMetaObject()->signalOffset() + 1 );
}

bool gui::DllSelectorDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: done((int)static_QUType_int.get(_o+1)); break;
    case 1: accept(); break;
    case 2: reject(); break;
    case 3: loadModuleClass(); break;
    case 4: unloadModuleClass(); break;
    case 5: setShown((bool)static_QUType_bool.get(_o+1)); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool gui::DllSelectorDialog::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: status((const std::string&)*((const std::string*)static_QUType_ptr.get(_o+1))); break;
    case 1: closed(); break;
    default:
	return QDialog::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool gui::DllSelectorDialog::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool gui::DllSelectorDialog::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
